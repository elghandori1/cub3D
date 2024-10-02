/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:43:52 by sait-alo          #+#    #+#             */
/*   Updated: 2024/10/01 12:12:39 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_window(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		ft_error(game, "Failed to init mlx\n");
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (ft_error(game, "Failed to init mlx win\n"));
	game->screen_middle = (double)(HEIGHT) / 2;
}

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
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
