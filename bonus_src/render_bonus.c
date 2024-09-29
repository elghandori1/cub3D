/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:16:51 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 15:58:40 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_image	*set_wall_texture(t_game *g, t_ray r)
{
	if (r.hit_content == 'D')
		return (g->textures[DOOR]);
	else if (r.hit_content == 'R')
		return (g->textures[SHOOT_BOARD]);
	return (g->textures[WEST]);
}

static void	render_ceiling(t_game *g, int ray_id, int start_y)
{
	int	y;

	y = -1;
	while (++y < start_y + 10)
		put_pixels(&g->frame_buffer, ray_id, y, get_color(g->data->ciel_color));
}

void	render_wall(t_game *g, t_ray ray, t_wall *wall)
{
	const int	*addr = (int *)wall->texture->addr;
	int			ty;
	int			color;
	double		distance_from_top;
	int			y;

	y = wall->start_y + 1;
	while (y < wall->end_y)
	{
		distance_from_top = y + (wall->height / 2) - g->screen_center;
		ty = (int)(distance_from_top * (wall->texture->width / wall->height));
		if (wall->tx >= 0 && ty <= wall->texture->width \
			&& ((ty * wall->texture->width) + wall->tx) >= 0)
			color = addr[ty * wall->texture->width + wall->tx];
		put_pixels(&g->frame_buffer, ray.id, y, color);
		y++;
	}
}

static void	render_floor(t_game *g, int rid, int wall_end)
{
	while (wall_end < HEIGHT)
	{
		put_pixels(&g->frame_buffer, rid, \
			wall_end, get_color(g->data->floor_color));
		wall_end++;
	}
}

void	render_wall_strip(t_game *g, t_ray ray)
{
	t_wall	wall;

	ray.distance *= cos(g->data->player.angle - ray.angle);
	wall.height = (SIZE / ray.distance) * DISTANCE_PROJ_PLANE;
	wall.end_y = g->screen_center + (wall.height / 2);
	wall.start_y = g->screen_center - (wall.height / 2);
	wall.texture = set_wall_texture(g, ray);
	if (wall.start_y < 0)
		wall.start_y = 0;
	if (wall.end_y > HEIGHT)
		wall.end_y = HEIGHT;
	if (ray.was_hit_vertical)
		wall.tx = (int)ray.wall_hit.y % SIZE;
	else
		wall.tx = (int)ray.wall_hit.x % SIZE;
	render_ceiling(g, ray.id, wall.start_y);
	render_wall(g, ray, &wall);
	render_floor(g, ray.id, wall.end_y);
}
