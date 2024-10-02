/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:22:43 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/30 18:26:43 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_point	hinter(t_game *g, t_ray *ray, t_point delta)
{
	t_point			inter;
	const t_player	*player = &g->data->player;
	const int		pixel = ray->facing_up;

	inter.y = (int)(player->y / SIZE) * SIZE + (delta.y > 0) * SIZE;
	inter.x = player->x + (inter.y - player->y) / tan(ray->angle);
	while (wall_hit(inter.x, inter.y - pixel, g))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	return (inter);
}

static t_point	vinter(t_game *g, t_ray *r, t_point delta)
{
	t_point			inter;
	const t_player	*player = &g->data->player;
	const int		pixel = !r->facing_right;

	inter.x = (int)(player->x / SIZE) * SIZE + (delta.x > 0) * SIZE;
	inter.y = player->y + (inter.x - player->x) * tan(r->angle);
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

void	cast_ray(t_game *g, t_ray *r)
{
	t_point			stp;
	t_point			vhit;
	t_point			hhit;
	t_point			dis;

	set_ray_direction(r, &stp);
	vhit = vinter(g, r, (t_point){stp.x * SIZE, stp.x * SIZE * tan(r->angle)});
	hhit = hinter(g, r, (t_point){stp.y * SIZE / tan(r->angle), stp.y * SIZE});
	dis.x = get_distance(g->data->player.x, g->data->player.y, vhit.x, vhit.y);
	dis.y = get_distance(g->data->player.x, g->data->player.y, hhit.x, hhit.y);
	if (dis.x < dis.y)
	{
		r->distance = dis.x;
		r->dir = "EW"[vhit.x < g->data->player.x];
		r->wall_hit = vhit;
	}
	else
	{
		r->dir = "SN"[hhit.y < g->data->player.y];
		r->distance = dis.y;
		r->wall_hit = hhit;
	}
	r->was_hit_vertical = (dis.x < dis.y);
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
