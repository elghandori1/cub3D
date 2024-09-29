/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:22:43 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 16:00:37 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_point	ray_hor_intersect(t_game *g, t_ray *ray, t_point delta)
{
	t_point	inter;
	int		pixel;

	inter.y = (int)(g->data->player.y / SIZE) * SIZE + (delta.y > 0) * SIZE;
	inter.x = g->data->player.x \
			+ (inter.y - g->data->player.y) / tan(ray->angle);
	pixel = 1 - 2 * !ray->facing_up;
	while (wall_hit(inter.x, inter.y - pixel, g))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	return (inter);
}

t_point	ray_ver_intersect(t_game *g, t_ray *ray, t_point delta)
{
	t_point	inter;
	int		pixel;

	inter.x = (int)(g->data->player.x / SIZE) * SIZE + (delta.x > 0) * SIZE;
	inter.y = g->data->player.y \
			+ (inter.x - g->data->player.x) * tan(ray->angle);
	pixel = 1 - 2 * ray->facing_right;
	while (wall_hit(inter.x - pixel, inter.y, g))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	return (inter);
}

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void	cast_ray(t_game *g, t_ray *ray)
{
	t_point			stp;
	t_point			vhit;
	t_point			hhit;
	t_point			dis;

	set_ray_direction(ray, &stp);
	vhit = ray_ver_intersect(g, ray, \
			(t_point){stp.x * SIZE, stp.x * SIZE * tan(ray->angle)});
	hhit = ray_hor_intersect(g, ray, \
			(t_point){stp.y * SIZE / tan(ray->angle), stp.y * SIZE});
	dis.x = get_distance(g->data->player.x, g->data->player.y, vhit.x, vhit.y);
	dis.y = get_distance(g->data->player.x, g->data->player.y, hhit.x, hhit.y);
	if (dis.x < dis.y)
	{
		ray->distance = dis.x;
		ray->dir = "EW"[vhit.x < g->data->player.x];
		ray->wall_hit = vhit;
	}
	else
	{
		ray->dir = "SN"[hhit.y < g->data->player.y];
		ray->distance = dis.y;
		ray->wall_hit = hhit;
	}
	ray->was_hit_vertical = (dis.x < dis.y);
}

int	raycasting(t_game *game, t_ray *rays)
{
	int		ray;
	double	ray_angle;
	double	anc;

	ray = -1;
	ray_angle = game->data->player.angle - (FOV_RD / 2);
	anc = FOV_RD / WIDTH;
	while (++ray < WIDTH)
	{
		rays[ray].id = ray;
		ray_angle = normalize_angle(ray_angle);
		rays[ray].angle = ray_angle;
		cast_ray(game, &rays[ray]);
		render_wall_strip(game, rays[ray]);
		ray_angle += anc;
	}
	return (0);
}
