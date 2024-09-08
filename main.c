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
	mlx_hook(game->mlx_win, 2, (1L << 0), game_events, game);
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

void render_wall(t_game *g, t_ray ray)
{
	double wall_h;
	double bp;
	double tp;
	int tx;
	int ty;
	int color;
	int *texture;
	texture = g->textures[1];

	wall_h = (SIZE / ray.distance) * ((WIDTH / 2) / tan(FOV_RD / 2));
	bp = (HEIGHT / 2) + (wall_h / 2);
	tp = (HEIGHT / 2) - (wall_h / 2);
	if (bp >= HEIGHT)
		bp = HEIGHT;
	if (tp <= 0)
		tp = 0;
	// draw wall
	if (ray.was_hit_vertical)
		tx = (int)ray.wall_hit.y % SIZE;
	else
		tx = (int)ray.wall_hit.x % SIZE;
	tx = (tx * 64) / SIZE;
	while (bp < tp)
	{
		ty = (int)((bp - (HEIGHT / 2) + (wall_h / 2)) * (64 / wall_h));
		ty = ty % 64;
		color = 0xFFFFFFFF;
		my_mlx_pixel_put(&g->frame_buffer, ray.id, bp++, color);
	}
	while (bp < HEIGHT)
		my_mlx_pixel_put(&g->frame_buffer, ray.id, bp++, get_color(g->data->floor_color));
	tp = 0;
	while (tp < (HEIGHT / 2) - (wall_h / 2))
		my_mlx_pixel_put(&g->frame_buffer, ray.id, tp++, get_color(g->data->ciel_color));
}

int rendering(void *data)
{
    t_game *game;
    t_ray ray[WIDTH];

    game = (t_game *)data;

	ft_memset(game->frame_buffer.addr, 0, WIDTH * HEIGHT * 4);
	move_player(game);
    raycasting(game, ray);
	// render_map(game);
	// render_player(game, &game->data->player);
    mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->frame_buffer.img, 0, 0);
	// mlx_destroy_image(game->mlx_ptr, game->frame_buffer.img);
    return (0);
}

int	*load_texture(t_game *game, char *path)
{
	int		n;
	void	*img;
	int 	*addr;
	
	img = mlx_xpm_file_to_image(game->mlx_ptr, path, &n, &n);
	if (!img)
		ft_error(game, "Error\nTexture loading failed\n"); // need to check if all the mem are freed !!
	addr = (int *)mlx_get_data_addr(img, &n, &n, &n);
	return (addr);
}

void	load_textures(t_game *game)
{
	game->textures[0] = load_texture(game, game->data->no_texture);
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
