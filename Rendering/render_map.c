#include "../cub3D.h"

void	render_map(t_game *game)
{
	t_img img;
	int x = 0, y = 0, i = 0, j = 0;
	int color = 0;
	img.img = mlx_new_image(game->mlx_ptr, HEIGHT, WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	while (y < game->map->height)
	{
		x = 0;
		while (x < ft_strlen(game->map->map[y]))
		{
			if (game->map->map[y][x] == '1')
				color = 0xFFFFFF;
			else if (game->map->map[y][x] == '0' || ft_search(game->map->map[y][x], "NSEW"))
				color = 0x808080;
			else
				color = 0x0;
			put_pixels(&img, color, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, img.img, 0,  0);
}