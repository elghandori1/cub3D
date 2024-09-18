#include "../cub3d_bonus.h"

void	put_pixels(t_image *data, int x, int y, int color)
{
	char	*dst;
    
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

