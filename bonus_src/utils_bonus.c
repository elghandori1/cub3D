#include "cub3d_bonus.h"

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += PI2;
	else if (angle > PI2)
		angle -= PI2;
	return (angle);
}

int	get_color(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

void	put_pixels(t_image *data, int x, int y, int color)
{
	char	*dst;
    
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
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

// int	key_release(int key, t_game *game)
// {
// 	if (key == W)
// 		game->data->player.keys.up = 0;
// 	if (key == S)
// 		game->data->player.keys.down = 0;
// 	if (key == A)
// 		game->data->player.keys.left = 0;
// 	if (key == D)
// 		game->data->player.keys.right = 0;
// 	if (key == LEFT)
// 		game->data->player.keys.rot_left = 0;
// 	if (key == RIGHT)
// 		game->data->player.keys.rot_right = 0;
// 	return (0);
// }
