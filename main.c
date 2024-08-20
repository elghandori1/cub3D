#include "cub3D.h"

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	render_map(t_game *game)
{
	int x = 0, y = 0, i = 0, j = 0;
	int color = 0;
	t_data img;
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
			else if (game->map->map[y][x] == '0')
				color = 0x808080;
			else
				color = 0x0;
			for (i = 0; i < 32; i++) { 
				for (j = 0; j < 32; j++) {
					my_mlx_pixel_put(&img, x * (SIZE / 2) + i, y * (SIZE / 2) + j, color);
				}
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, img.img, 0,  0);
}

void	render_player(t_game *game)
{
	int x = 0, y = 0, i = 0, j = 0;
	int color = 0;
	t_data img;
	img.img = mlx_new_image(game->mlx_ptr, HEIGHT, WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
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
	render_map(cub3d);
	render_player(cub3d);
	mlx_loop(cub3d->mlx_ptr);
	free_cub3d(cub3d);
	return 0;
}
