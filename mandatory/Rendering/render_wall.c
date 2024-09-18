#include "../../cub3D.h"

t_image	*set_wall_texture(t_game *g, t_ray r)
{
	if (r.dir == 'N')
		return (g->textures[0]);
	else if (r.dir == 'S')
		return (g->textures[1]);
	else if (r.dir == 'W')
		return (g->textures[2]);
	else if (r.dir == 'E')
		return (g->textures[3]);
	return (NULL);
}

void	calculate_wall_texture(t_game *g, t_ray ray, t_wall_data *wall_data)
{
	wall_data->wall_h = (SIZE / ray.distance) * DISTANCE_PROJ_PLANE;
	wall_data->start_y = (HEIGHT / 2) - (wall_data->wall_h / 2);
	wall_data->end_y = (HEIGHT / 2) + (wall_data->wall_h / 2);
	if (wall_data->start_y < 0)
		wall_data->start_y = 0;
	if (wall_data->end_y > HEIGHT)
		wall_data->end_y = HEIGHT;
	wall_data->texture = set_wall_texture(g, ray);
	if (ray.was_hit_vertical)
		wall_data->tx = (int)ray.wall_hit.y % SIZE;
	else
		wall_data->tx = (int)ray.wall_hit.x % SIZE;
}

void	render_ceiling(t_game *g, int ray_id, int start_y)
{
	int	y;

	y = 0;
	while (y < start_y + 10)
	{
		put_pixels(&g->frame_buffer, ray_id, y, get_color(g->data->ciel_color));
		y++;
	}
}

void	render_wall_and_floor(t_game *g, t_ray ray, t_wall_data *wall_data)
{
	int		*addr;
	int		y;
	double	distance_from_top;

	int (ty), (color);
	y = wall_data->start_y + 1;
	addr = (int *)wall_data->texture->addr;
	while (y < wall_data->end_y)
	{
		distance_from_top = y + (wall_data->wall_h / 2) - (HEIGHT / 2);
		ty = (int)(distance_from_top * (wall_data->texture->width
					/ wall_data->wall_h)) % wall_data->texture->width;
		if (wall_data->tx >= 0 && ty <= wall_data->texture->width && ((ty
					* wall_data->texture->width) + wall_data->tx) >= 0)
			color = addr[ty * wall_data->texture->width + wall_data->tx];
		put_pixels(&g->frame_buffer, ray.id, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		put_pixels(&g->frame_buffer, ray.id, y,
			get_color(g->data->floor_color));
		y++;
	}
}

void	render_wall(t_game *g, t_ray ray)
{
	t_wall_data	wall_data;

	calculate_wall_texture(g, ray, &wall_data);
	render_ceiling(g, ray.id, wall_data.start_y);
	render_wall_and_floor(g, ray, &wall_data);
}
