/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:05:14 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 14:48:09 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_point	ray_hor_intersect(t_game *g, t_ray *ray, t_point delta)
{
	t_point	inter;
	int		pixel;
	int		x;
	int		y;

	inter.y = (int)(g->data->player.y / SIZE) * SIZE + (delta.y > 0) * SIZE;
	inter.x = g->data->player.x \
				+ (inter.y - g->data->player.y) / tan(ray->angle);
	pixel = 1 - 2 * !ray->facing_up;
	while (wall_hit(inter.x, inter.y - pixel, g, ray))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	x = (int)(inter.x / SIZE);
	y = (int)((inter.y - pixel) / SIZE);
	if (inter.x > 0 && inter.x < g->data->width * SIZE \
		&& inter.y > 0 && inter.y < g->data->height * SIZE)
		ray->hhit_content = g->data->square_map[y][x];
	return (inter);
}

t_point	ray_ver_intersect(t_game *g, t_ray *ray, t_point delta)
{
	t_point	inter;
	int		pixel;
	int		x;
	int		y;

	inter.x = (int)(g->data->player.x / SIZE) * SIZE + (delta.x > 0) * SIZE;
	inter.y = g->data->player.y \
				+ (inter.x - g->data->player.x) * tan(ray->angle);
	pixel = 1 - 2 * ray->facing_right;
	while (wall_hit(inter.x - pixel, inter.y, g, ray))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	x = (int)((inter.x - pixel) / SIZE);
	y = (int)(inter.y / SIZE);
	if (inter.x > 0 && inter.x < g->data->width * SIZE \
		&& inter.y > 0 && inter.y < g->data->height * SIZE)
		ray->vhit_content = g->data->square_map[y][x];
	return (inter);
}

/*
	sets the ray direction based on its angle 
	then set a value the andicate where the player is facing
	-1 if ray is facing left, 1 if ray is facing right
	-1 if ray is facing up, 1 if ray is facing down
*/
void	set_ray_direction(t_ray *ray, t_point *stp)
{
	if (ray->angle > PI)
		ray->facing_up = 1;
	else
		ray->facing_up = 0;
	if ((ray->angle <= PI_2 || ray->angle > 3 * PI_2))
		ray->facing_right = 1;
	else
		ray->facing_right = 0;
	stp->x = 1 - 2 * !ray->facing_right;
	stp->y = 1 - 2 * ray->facing_up;
}

void	cast_ray(t_game *g, t_ray *ray)
{
	t_point		vhit;
	t_point		hhit;
	t_point		stp;
	t_point		distance;

	set_ray_direction(ray, &stp);
	vhit = ray_ver_intersect(g, ray, \
		(t_point){stp.x * SIZE, stp.x * SIZE * tan(ray->angle)});
	hhit = ray_hor_intersect(g, ray, \
		(t_point){stp.y * SIZE / tan(ray->angle), stp.y * SIZE});
	distance.x = sqrt(pow(g->data->player.x - vhit.x, 2) \
						+ pow(g->data->player.y - vhit.y, 2));
	distance.y = sqrt(pow(g->data->player.x - hhit.x, 2) \
						+ pow(g->data->player.y - hhit.y, 2));
	if (distance.x > distance.y)
		set_ray_hit_horizontal(ray, hhit, distance.y, g->data->player.y);
	else
		set_ray_hit_vertical(ray, vhit, distance.x, g->data->player.x);
}

int	raycasting(t_game *game, t_ray *rays)
{
	int		ray;
	double	ray_angle;
	double	anc;

	ray = -1;
	anc = FOV_RD / WIDTH;
	ray_angle = game->data->player.angle - (FOV_RD / 2);
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
