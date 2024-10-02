/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:05:14 by sait-alo          #+#    #+#             */
/*   Updated: 2024/10/01 14:18:29 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_point	hinter(t_game *g, t_ray *ray, t_point delta)
{
	t_point			inter;
	const t_player	*player = &g->data->player;
	const int		pixel = ray->facing_up;
	int				x;
	int				y;

	inter.y = (int)(player->y / SIZE) * SIZE + (delta.y > 0) * SIZE;
	inter.x = player->x + (inter.y - player->y) / tan(ray->angle);
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

static t_point	vinter(t_game *g, t_ray *ray, t_point delta)
{
	t_point			inter;
	const t_player	*player = &g->data->player;
	const int		pixel = !ray->facing_right;
	int				x;
	int				y;

	inter.x = (int)(player->x / SIZE) * SIZE + (delta.x > 0) * SIZE;
	inter.y = player->y + (inter.x - player->x) * tan(ray->angle);
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

void	cast_ray(t_game *g, t_ray *r)
{
	t_point		vhit;
	t_point		hhit;
	t_point		stp;
	t_point		dis;

	set_ray_direction(r, &stp);
	vhit = vinter(g, r, (t_point){stp.x * SIZE, stp.x * SIZE * tan(r->angle)});
	hhit = hinter(g, r, (t_point){stp.y * SIZE / tan(r->angle), stp.y * SIZE});
	dis.x = get_distance(g->data->player.x, g->data->player.y, vhit.x, vhit.y);
	dis.y = get_distance(g->data->player.x, g->data->player.y, hhit.x, hhit.y);
	if (dis.x < dis.y)
	{
		r->distance = dis.x;
		r->wall_dir = "EW"[vhit.x < g->data->player.x];
		r->wall_hit = vhit;
		r->hit_content = r->vhit_content;
	}
	else
	{
		r->wall_dir = "SN"[hhit.y < g->data->player.y];
		r->distance = dis.y;
		r->wall_hit = hhit;
		r->hit_content = r->hhit_content;
	}
	r->was_hit_vertical = (dis.x < dis.y);
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
