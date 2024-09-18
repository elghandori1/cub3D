#include "../cub3d_bonus.h"

static t_image	*set_wall_texture(t_game *g, t_ray r)
{
	if (r.hit_content == 'D')
		return (g->door_texture);
	if (r.hit_content == 'R')
		return (g->textures[4]);
	if (r.wall_dir == 'N')
		return (g->textures[0]);
	else if (r.wall_dir == 'S')
		return (g->textures[1]);
	else if (r.wall_dir == 'W')
		return (g->textures[2]);
	else if (r.wall_dir == 'E')
		return (g->textures[3]);
	return (g->textures[0]);
}

void	render_wall_strip(t_game *g, t_ray ray)
{
	t_image *texture;
	double 	wall_h;
	int 	start_y, end_y;
	int 	tx, ty;
	int 	color;
	double	distance_from_top;
	int 	y;

	texture = set_wall_texture(g, ray);
	wall_h = (SIZE / ray.distance) * DISTANCE_PROJ_PLANE;
	start_y = (HEIGHT / 2) - (wall_h / 2);
	end_y = (HEIGHT / 2) + (wall_h / 2);
	int *addr = (int *)texture->addr;

	if (start_y < 0)
		start_y = 0;
	if (end_y > HEIGHT)
		end_y = HEIGHT;

	if (ray.was_hit_vertical)
		tx = (int)ray.wall_hit.y % SIZE;
	else
		tx = (int)ray.wall_hit.x % SIZE;
	tx  = (tx * texture->width) / SIZE;
	y = 0;
	while (y < start_y + 10)
	{
		put_pixels(&g->frame_buffer, ray.id, y, get_color(g->data->ciel_color));    	
		y++;
	}
	y = start_y + 1;
	while (y < end_y)
	{
		distance_from_top = y + (wall_h / 2) - (HEIGHT / 2);
		ty = (int)(distance_from_top * (texture->width / wall_h));
		ty = ty % texture->height;
		if (tx >= 0 && ty <= texture->width && ((ty * texture->width) + tx) >= 0)
			color = addr[ty * texture->width + tx];
		put_pixels(&g->frame_buffer, ray.id, y, color);		
		y++;
	}
	y = end_y;
	while (y < HEIGHT)
	{
	    put_pixels(&g->frame_buffer, ray.id, y, get_color(g->data->floor_color));
		y++;
	}
}
