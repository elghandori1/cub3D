#include "cub3D.h"

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
	game->mlx_win = mlx_new_window(game->mlx_ptr, 1280, 960, "cub3D"); // 640x 480 // 1280x960
	if (!game->mlx_win)
		return (-1);
	return (0);
}

void	render_map(t_game *game)
{
	int x = 0, y = 0, i = 0, j = 0;
	int color = 0;
	char **map;
	int px, py;

	map = game->map->map;
	while (y < game->map->len)
	{
		x = 0;
		while (x < ft_strlen(map[y]))
		{
			if (map[y][x] == '1')
				color = 0xFFFFFF;
			else if (map[y][x] == '0')
				color = 0x808080;
			else if (map[y][x] == 'N')
				color = 0xFF0000;
			else if (map[y][x] == ' ')
				color = 0x0;
			px = x * 10;
			py = y * 10;
			i = 0;
			while (i < 10)
			{
				j = 0;
				while (j < 10)
				{
					mlx_pixel_put(game->mlx_ptr, game->mlx_win, px + i, py + j, color);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
	t_game *cub3d;
	
	cub3d = instance();
	if (ac != 2)
		ft_error(cub3d, "Error: Usage: ./cub3d <map_file.cub>\n");
	check_map(&cub3d, av[1]);
	// RENDERING 
	// TODO : RENDER 2D MAP ON THE SCREEN
	if (window_init(cub3d))
		return (EXIT_FAILURE);
	// char **map = cub3d->map->map;

	// int x = 0, y = 0;
	// while (map[y])
	// {
	// 	printf("%s", map[y]);
	// 	y++;
	// }
	render_map(cub3d);
	mlx_loop(cub3d->mlx_ptr);
	free_cub3d(cub3d);
	return 0;
}
