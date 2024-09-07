#include "../cub3D.h"
void	draw_square(t_image *img, int color, int x, int y)
{
	int i = 0;
	int j = 0;

	while (++i < SIZE)
	{
		j = 0;
		while (++j < SIZE)
		{
			put_pixels(img, color, x * SIZE + j, y * (SIZE) + i);
		}
	}
}

void	render_map(t_game *game)
{
	t_image img;

	int x = 0, y = 0, i = 0, j = 0;
	int color = 0;
	img.img = mlx_new_image(game->mlx_ptr, HEIGHT, WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	while (y < game->data->height)
	{
		x = 0;
		while (x < game->data->width)
		{
			if (game->data->map[y][x] == '1')
				color = 0xFFFFFF;
			else if (game->data->map[y][x] == '0' || ft_search(game->data->map[y][x], "NSEW"))
				color = 0x808080;
			else
				color = 0x0;
			draw_square(&img, color, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, img.img, 0,  0);
	mlx_destroy_image(game->mlx_ptr, img.img);
}
