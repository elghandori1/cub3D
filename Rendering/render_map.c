#include "../cub3D.h"
void	draw_square(t_image *img, int color, int x, int y)
{
	int i = 0;
	int j = 0;

	while (++i < MAP_SCALE)
	{
		j = 0;
		while (++j < MAP_SCALE)
		{
			my_mlx_pixel_put(img, x * MAP_SCALE + j, y * MAP_SCALE + i, color);
			// my_mlx_pixel_put(img, color, x * SIZE + j, y * (SIZE) + i);
		}
	}
}

void	render_map(t_game *game)
{
	int x = 0, y = 0, i = 0, j = 0;
	int color = 0;

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
			draw_square(&game->frame_buffer, color, x, y);
			x++;
		}
		y++;
	}
}
