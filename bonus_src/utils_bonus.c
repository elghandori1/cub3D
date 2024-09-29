/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:13:47 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 12:14:21 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	wall_hit(double x, double y, t_game *g, t_ray *ray)
{
	int	x1;
	int	y1;

	x1 = (int)(x / SIZE);
	y1 = (int)(y / SIZE);
	if (x > 0 && x < g->data->width * SIZE \
		&& y > 0 && y < g->data->height * SIZE)
	{
		if (ft_strchr("1DR", g->data->square_map[y1][x1]))
			return (0);
		else if (ray->skip_closed_door && g->data->square_map[y1][x1] == 'd')
			return (0);
		else
			return (1);
	}
	return (0);
}
