/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:47:18 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 15:56:18 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_ray_hit_vertical(t_ray *ray, t_point hit, \
		double distance, double player_x)
{
	ray->hit_content = ray->vhit_content;
	ray->wall_bottom = "EW"[hit.x < player_x];
	ray->distance = distance;
	ray->wall_hit = hit;
	ray->was_hit_vertical = 1;
}

void	set_ray_hit_horizontal(t_ray *ray, t_point hit, \
			double distance, double player_y)
{
	ray->hit_content = ray->hhit_content;
	ray->wall_dir = "SN"[hit.y < player_y];
	ray->distance = distance;
	ray->wall_hit = hit;
	ray->was_hit_vertical = 0;
}
