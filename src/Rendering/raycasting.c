#include "../../cub3D.h"

t_point	ray_hor_intersect(t_game *g, t_ray *ray, t_point delta)
{
	t_point	inter;
	int		pixel;

	inter.y = (int)(g->data->player.y / SIZE) * SIZE + (delta.y > 0) * SIZE;
	inter.x = g->data->player.x + (inter.y - g->data->player.y)
		/ tan(ray->angle);
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
	inter.y = g->data->player.y + (inter.x - g->data->player.x)
		* tan(ray->angle);
	pixel = 1 - 2 * ray->facing_right;
	while (wall_hit(inter.x - pixel, inter.y, g))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	return (inter);
}

void	cast_ray(t_game *g, t_ray *ray)
{
	t_point	vhit;
	t_point	hhit;
	t_point	stp;
	double	dis1;
	double	dis2;

	set_ray_direction(ray);
	stp.x = 1 - 2 * !ray->facing_right;
	stp.y = 1 - 2 * ray->facing_up;
	vhit = ray_ver_intersect(g, ray, (t_point){stp.x * SIZE, stp.x * SIZE
			* tan(ray->angle)});
	dis1 = sqrt(pow(g->data->player.x - vhit.x, 2) + pow(g->data->player.y
				- vhit.y, 2));
	hhit = ray_hor_intersect(g, ray, (t_point){stp.y * SIZE / tan(ray->angle),
			stp.y * SIZE});
	dis2 = sqrt(pow(g->data->player.x - hhit.x, 2) + pow(g->data->player.y
				- hhit.y, 2));
	if (dis1 < dis2)
	{
		ray->distance = dis1;
		ray->dir = "EW"[vhit.x < g->data->player.x];
		ray->was_hit_vertical = 1;
		ray->wall_hit = vhit;
	}
	else
	{
		ray->dir = "SN"[hhit.y < g->data->player.y];
		ray->distance = dis2;
		ray->was_hit_vertical = 0;
		ray->wall_hit = hhit;
	}
	ray->distance *= cos(g->data->player.angle - ray->angle);
}

int	raycasting(t_game *game, t_ray *rays)
{
	int		ray;
	double	ray_angle;
	double	anc;

	ray = -1;
	anc = FOV_RD / WIDTH - 0.0001;
	ray_angle = game->data->player.angle - (FOV_RD / 2);
	while (++ray < WIDTH)
	{
		rays[ray].id = ray;
		ray_angle = normalize_angle(ray_angle);
		rays[ray].angle = ray_angle;
		cast_ray(game, &rays[ray]);
		render_wall(game, rays[ray]);
		ray_angle += anc;
	}
	return (0);
}
