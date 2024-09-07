#include "../cub3D.h"

int wall_hit(double x, double y, t_game *g)
{
	return ((x > 0 && x < g->data->width * SIZE && y > 0 && y < g->data->height * SIZE
		&& g->data->map[(int)(y / SIZE)][(int)(x / SIZE)] != '1'));
}

double ray_hor_intersect(t_game *g, t_ray *ray, t_point delta)
{
	t_point	inter;
	int		pixel;

	inter.y = (int)(g->data->player.y / SIZE) * SIZE + (delta.y > 0) * SIZE;
	inter.x = g->data->player.x + (inter.y - g->data->player.y) / tan(ray->angle);
	pixel = 1 - 2 * !ray->facing_up;
	while (wall_hit(inter.x , inter.y - pixel , g))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	return (sqrt(pow(inter.x - g->data->player.x, 2) + pow(inter.y - g->data->player.y, 2)));
}

double ray_ver_intersect(t_game *g, t_ray *ray, t_point delta)
{
	t_point	inter;
	int		pixel;

	inter.x = (int)(g->data->player.x / SIZE) * SIZE + (delta.x > 0) * SIZE;
	inter.y = g->data->player.y + (inter.x - g->data->player.x) * tan(ray->angle);
	pixel = 1 - 2 * ray->facing_right;
	while (wall_hit(inter.x - pixel, inter.y, g))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	return (sqrt(pow(inter.x - g->data->player.x, 2) + pow(inter.y - g->data->player.y, 2)));
}

void	set_ray_direction(t_ray *ray)
{
	if (ray->angle > PI)
		ray->facing_up = 1;
	else
		ray->facing_up = 0;
	if ((ray->angle <= PI_2 || ray->angle > 3 * PI_2))
		ray->facing_right = 1;
	else
		ray->facing_right = 0;
}

void	cast_ray(t_game *g, t_ray *ray)
{
	t_point		hit;
	t_point 	stp;

	set_ray_direction(ray);
	stp.x = 1 - 2 * !ray->facing_right; // -1 if ray is facing left, 1 if ray is facing right
	stp.y = 1 - 2 * ray->facing_up; // -1 if ray is facing up, 1 if ray is facing down
	hit.x = ray_ver_intersect(g, ray, (t_point){stp.x * SIZE, stp.x * SIZE * tan(ray->angle)});
	hit.y = ray_hor_intersect(g, ray, (t_point){stp.y * SIZE / tan(ray->angle), stp.y * SIZE});
	if (hit.x < hit.y)
	{
		ray->distance = hit.x;
		ray->was_hit_vertical = 1;
		ray->wall_hit = (t_point){g->data->player.x + hit.x * cos(ray->angle), g->data->player.y + hit.x * sin(ray->angle)};
	}
	else
	{
		ray->distance = hit.y;
		ray->was_hit_vertical = 0;
		ray->wall_hit = (t_point){g->data->player.x + hit.y * cos(ray->angle), g->data->player.y + hit.y * sin(ray->angle)};
	}
	ray->distance *= cos(g->data->player.angle - ray->angle);
}


int raycasting(t_game *game, t_ray *rays)
{
    int     ray;
    double  ray_angle;
	double anc;

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