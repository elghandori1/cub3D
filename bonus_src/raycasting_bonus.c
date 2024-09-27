#include "cub3d_bonus.h"

int wall_hit(double x, double y, t_game *g, t_ray *ray)
{
    int x1, y1;
    x1 = floor((x / SIZE));
    y1 = floor(y / SIZE);
    if (x > 0 && x < g->data->width * SIZE && y > 0 && y < g->data->height * SIZE)
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


t_point ray_hor_intersect(t_game *g, t_ray *ray, t_point delta)
{
	t_point	inter;
	int		pixel;

	inter.y = (int)(g->data->player.y / SIZE) * SIZE + (delta.y > 0) * SIZE;
	inter.x = g->data->player.x + (inter.y - g->data->player.y) / tan(ray->angle);
	pixel = 1 - 2 * !ray->facing_up;
	while (wall_hit(inter.x , inter.y - pixel , g, ray))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	if (inter.x > 0 && inter.x < g->data->width * SIZE && inter.y > 0 && inter.y < g->data->height * SIZE)
		ray->hhit_content = g->data->square_map[(int)((inter.y - pixel) / SIZE)][(int)(inter.x / SIZE)];
	return (inter);
}

t_point ray_ver_intersect(t_game *g, t_ray *ray, t_point delta)
{
	t_point	inter;
	int		pixel;

	inter.x = (int)(g->data->player.x / SIZE) * SIZE + (delta.x > 0) * SIZE;
	inter.y = g->data->player.y + (inter.x - g->data->player.x) * tan(ray->angle);
	pixel = 1 - 2 * ray->facing_right;
	while (wall_hit(inter.x - pixel, inter.y, g, ray))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	if (inter.x > 0 && inter.x < g->data->width * SIZE && inter.y > 0 && inter.y < g->data->height * SIZE)
		ray->vhit_content = g->data->square_map[(int)(inter.y / SIZE)][(int)((inter.x - pixel) / SIZE)];
	return (inter);
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
	t_point		vhit;
	t_point		hhit;
	t_point 	stp;

	set_ray_direction(ray);
	stp.x = 1 - 2 * !ray->facing_right; // -1 if ray is facing left, 1 if ray is facing right
	stp.y = 1 - 2 * ray->facing_up; // -1 if ray is facing up, 1 if ray is facing down
	vhit = ray_ver_intersect(g, ray, (t_point){stp.x * SIZE, stp.x * SIZE * tan(ray->angle)});
	hhit = ray_hor_intersect(g, ray, (t_point){stp.y * SIZE / tan(ray->angle), stp.y * SIZE});
	double dis1 = sqrt(pow(g->data->player.x - vhit.x, 2) + pow(g->data->player.y - vhit.y, 2));
	double dis2 = sqrt(pow(g->data->player.x - hhit.x, 2) + pow(g->data->player.y - hhit.y, 2));
	if (dis1 < dis2)
	{
		ray->distance = dis1;
		ray->hit_content = ray->vhit_content;
		ray->wall_dir = "EW"[vhit.x < g->data->player.x];
		ray->was_hit_vertical = 1;
		ray->wall_hit = vhit;
	}
	else
	{
		ray->hit_content = ray->hhit_content;
		ray->wall_dir = "SN"[hhit.y < g->data->player.y];
		ray->distance = dis2;
		ray->was_hit_vertical = 0;
		ray->wall_hit = hhit;
	}
	ray->distance *= cos(g->data->player.angle - ray->angle);
}


int raycasting(t_game *game, t_ray *rays)
{
    int     ray;
    double  ray_angle;
	double anc;

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