#include "cub3D.h"

// TODO: i need to create a destructor incase of unexpected exit
t_game  *instance(void)
{
	static  t_game game;

	return (&game);
}
int	window_init(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (-1);
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (-1);
	return (0);
}

int		exit_game(void	*param)
{
	// free gc
	printf("quit\n");
	exit(1);
}

int		key_release(int key, t_game *game)
{
	if (key == W)
		game->data->player.keys.up = 0;
	if (key == S)
		game->data->player.keys.down = 0;
	if (key == A)
		game->data->player.keys.left = 0;
	if (key == D)
		game->data->player.keys.right = 0;
	if (key == LEFT)
		game->data->player.keys.rot_left = 0;
	if (key == RIGHT)
		game->data->player.keys.rot_right = 0;
	return (0);
}

void	capture_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, 2, (1L << 0), key_press, game);
	mlx_hook(game->mlx_win, 3, (1L << 1), key_release, game);
	mlx_hook(game->mlx_win, 17, (1L << 17), exit_game, NULL);
}

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += PI2;
	else if (angle > PI2)
		angle -= PI2;
	return (angle);
}

int	get_color(t_color *color)
{
	return (color->r << 16 | color->g << 8 | color->b);
}

t_image	*set_wall_texture(t_game *g, t_ray r)
{
	if (r.dir == 'N')
		return (g->textures[0]);
	else if (r.dir == 'S')
		return (g->textures[1]);
	else if (r.dir == 'W')
		return (g->textures[2]);
	else if (r.dir == 'E')
		return (g->textures[3]);
	return NULL;
}

void render_wall(t_game *g, t_ray ray)
{
	double wall_h;
	int 	start_y, end_y;
	int 	tx, ty;
	int 	color;
	t_image *texture;
	double	distance_from_top;
	int 	y;

	// TODO : set textures based on wall directions
	texture = set_wall_texture(g, ray);
	// texture = g->textures[3];
	wall_h = (SIZE / ray.distance) * DISTANCE_PROJ_PLANE;
	start_y = (HEIGHT / 2) - (wall_h / 2);
	end_y = (HEIGHT / 2) + (wall_h / 2);
	int *addr = (int *)texture->addr;
	if (start_y < 0)
		start_y = 0;
	if (end_y > HEIGHT)
		end_y = HEIGHT;

	if (ray.was_hit_vertical)
		tx = (int)ray.wall_hit.y % SIZE;
	else
		tx = (int)ray.wall_hit.x % SIZE;

	y = 0;
	while (y < start_y)
	{
	    my_mlx_pixel_put(&g->frame_buffer, ray.id, y, get_color(g->data->ciel_color));
		y++;
	}
	tx = (tx * texture->width) / texture->width;
	y = start_y + 1;
	while (y < end_y)
	{
		distance_from_top = y + (wall_h / 2) - (HEIGHT / 2);
		ty = (int)(distance_from_top * (texture->width / wall_h));
		ty = ty % texture->width;
		if (tx >= 0 && ty <= texture->width && ((ty * texture->width) + tx) >= 0)
			color = addr[ty * texture->width + tx];
		my_mlx_pixel_put(&g->frame_buffer, ray.id, y, color);		
		y++;
	}

	y = end_y;
	while (y < HEIGHT)
	{
	    my_mlx_pixel_put(&g->frame_buffer, ray.id, y, get_color(g->data->floor_color));
		y++;
	}
}

int rendering(void *data)
{
	t_game	*game;
	t_ray	ray[WIDTH];

	game = (t_game *)data;
	move_player(game);
	raycasting(game, ray);
	// render_map(game);
	// render_player(game, &game->data->player);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->frame_buffer.img, 0, 0);
	return (0);
}

t_image	*load_texture(t_game *game, char *path)
{
	int		n;
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->width, &img->height);
	if (!img->img)
		ft_error(game, "Error\nTexture loading failed\n"); // need to check if all the mem are freed !!
	img->addr = mlx_get_data_addr(img->img, &n, &n, &n);
	return (img);
}

void	load_textures(t_game *game)
{
	game->textures[0] = load_texture(game, game->data->no_texture); // i need to check for errors
	game->textures[1] = load_texture(game, game->data->so_texture);
	game->textures[2] = load_texture(game, game->data->we_texture);
	game->textures[3] = load_texture(game, game->data->ea_texture);
}

void	init_buffer(t_game *g)
{
	g->frame_buffer.img = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	if (!g->frame_buffer.img)
		ft_error(g ,"Error\nFrame buffer creation failed\n");
	g->frame_buffer.addr = mlx_get_data_addr(g->frame_buffer.img,
											&g->frame_buffer.bits_per_pixel,
											&g->frame_buffer.line_length,
											&g->frame_buffer.endian);
}

int main(int ac, char **av)
{
	t_game *game;
	
	if (ac != 2)
		return (ft_putstr_fd("Error:\nToo many args\n", 2), -1);
	game = instance();
	check_map(&game, av[1]);
	if (window_init(game))
		return (EXIT_FAILURE);
	
	load_textures(game);
	init_buffer(game);
	capture_hooks(game);
	mlx_loop_hook(game->mlx_ptr, &rendering, game);
	mlx_loop(game->mlx_ptr);
	free_cub3d(game);
	return (0);
}
