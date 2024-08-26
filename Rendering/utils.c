#include "../cub3D.h"

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
	while (++i < SIZE)
	{
		j = 0;
		while (++j < SIZE)
		{
			my_mlx_pixel_put(img, x * SIZE + i, y * SIZE + j, color);
		}
	}
}