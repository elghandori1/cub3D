#include "cub3D.h"

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

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
	game->mlx_win = mlx_new_window(game->mlx_ptr, HEIGHT, WIDTH, "cub3D"); // 640x 480 // 1280x960
	if (!game->mlx_win)
		return (-1);
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void	put_pixels(t_img *img, int color, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			my_mlx_pixel_put(img, x * SIZE + i, y * SIZE + j, color);
			j++;
		}
		i++;
	}
}

void	render_map(t_game *game)
{
	t_img img;
	int x = 0, y = 0, i = 0, j = 0;
	int color = 0;
	img.img = mlx_new_image(game->mlx_ptr, HEIGHT, WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	while (y < game->map->len)
	{
		x = 0;
		while (x < ft_strlen(game->map->map[y]))
		{
			if (game->map->map[y][x] == '1')
				color = 0xFFFFFF;
			else if (game->map->map[y][x] == '0' || ft_search(game->map->map[y][x], "NSEW"))
				color = 0x808080;
			else if (game->map->map[y][x] == ' ')
				color = 0x0;
			else
				color = 0xFFFFFF;
			put_pixels(&img, color, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, img.img, 0,  0);
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
        mlx_pixel_put(game->mlx_ptr, game->mlx_win, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void render_player(t_game *game, t_player *player)
{
    int px = player->x * SIZE;
    int py = player->y * SIZE;
    int color = 0xFF0000;
	int i;
	int j;

	i = 0;
	while (i < SIZE / 2)
	{
		j = 0;
		while (j <SIZE / 2)
		{
			mlx_pixel_put(game->mlx_ptr, game->mlx_win, px + i, py + j, color);
			j++;
		}
		i++;
	}
    int line_length = 30;
    int end_x = px + cos(player->angle) * line_length;
    int end_y = py - sin(player->angle) * line_length;  // Subtract because y-axis is inverted in most graphical systems
    draw_line(game, px, py, end_x, end_y, 0x00FF00);  // Green color for direction line
}

int		exit_game()
{
	// free gc
	printf("quit\n");
	exit(1);
}

int is_valid_position(t_game *game, int x, int y)
{
    return (x >= 0 && x < ft_strlen(game->map->map[0]) && y >= 0 && y < game->map->len && game->map->map[y][x] != '1');
}

void move_player_up(t_game *game)
{
    float new_x = game->map->player.x + game->map->player.dir_x * 0.2;
    float new_y = game->map->player.y + game->map->player.dir_y * 0.2;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        render_map(game);
        render_player(game, &game->map->player);
    }
}

void move_player_down(t_game *game)
{
    float new_x = game->map->player.x - game->map->player.dir_x * 0.2;
    float new_y = game->map->player.y - game->map->player.dir_y * 0.2;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        render_map(game);
        render_player(game, &game->map->player);
    }
}

void move_player_right(t_game *game)
{
    float perpendicular_x = -game->map->player.dir_y;
    float perpendicular_y = game->map->player.dir_x;
    float new_x = game->map->player.x + perpendicular_x * 0.2;
    float new_y = game->map->player.y + perpendicular_y * 0.2;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        render_map(game);
        render_player(game, &game->map->player);
    }
}

void move_player_left(t_game *game)
{
	
    float perpendicular_x = game->map->player.dir_y;
    float perpendicular_y = -game->map->player.dir_x;
    float new_x = game->map->player.x + perpendicular_x * 0.2;
    float new_y = game->map->player.y + perpendicular_y * 0.2;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        render_map(game);
        render_player(game, &game->map->player);
    }
}

void rotate_player_left(t_game *game)
{
    float rotation_speed = 0.1;
    game->map->player.angle -= rotation_speed;
    if (game->map->player.angle < 0)
        game->map->player.angle += 2 * PY;
    game->map->player.dir_x = cos(game->map->player.angle);
    game->map->player.dir_y = -sin(game->map->player.angle);
    render_map(game);
    render_player(game, &game->map->player);
}

void rotate_player_right(t_game *game)
{
    float rotation_speed = 0.1;
	
    game->map->player.angle += rotation_speed;
    if (game->map->player.angle > 2 * PY)
        game->map->player.angle -= 2 * PY;
    game->map->player.dir_x = cos(game->map->player.angle);
    game->map->player.dir_y = -sin(game->map->player.angle);
    render_map(game);
    render_player(game, &game->map->player);
}


int	game_events(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game();
	else if (keycode == W)
		move_player_up(game);
	else if (keycode == S)
		move_player_down(game);
	else if (keycode == A)
		move_player_left(game);
	else if (keycode == D)
		move_player_right(game);
    else if (keycode == 65363) // Left arrow key
        rotate_player_left(game);
    else if (keycode == 65361) // Right arrow key
        rotate_player_right(game);

	return (0);
}

void	capture_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, 17, 0, exit_game, NULL);
	mlx_hook(game->mlx_win, 2, (1L << 0), game_events, game);
}


int main(int ac, char **av)
{
	t_game *cub3d;
	
	cub3d = NULL;
	if (ac != 2)
		ft_error(cub3d, "Error: Usage: ./cub3d <map_file.cub>\n");
	cub3d = instance();
	check_map(&cub3d, av[1]);
	// RENDERING 
	// TODO : RENDER 2D MAP ON THE SCREEN
	// printf("%d\n", cub3d->map->len);
	// printf("%d\n", cub3d->map->max_len);
	// printf("%d\n", cub3d->map->rows);
	// exit(1);
	if (window_init(cub3d))
		return (EXIT_FAILURE);
	render_map(cub3d);
	render_player(cub3d, &cub3d->map->player);
	capture_hooks(cub3d);
	mlx_loop(cub3d->mlx_ptr);
	free_cub3d(cub3d);
	return 0;
}
