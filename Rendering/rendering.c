#include "../cub3D.h"

void	draw_line_step(t_point *start, t_line *params)
{
	int	e2;

	e2 = params->err;
	if (e2 > -params->dx)
	{
		params->err -= params->dy;
		start->x += params->sx;
	}
	if (e2 < params->dy)
	{
		params->err += params->dx;
		start->y += params->sy;
	}
}

void	draw_line(t_game *game, t_point start, t_point end, int color)
{
	t_line	params;

	params.dx = abs(end.x - start.x);
	params.dy = abs(end.y - start.y);
	params.sx = -1;
	params.sy = -1;
	if (start.x < end.x)
		params.sx = 1;
	if (start.y < end.y)
		params.sy = 1;
	if (params.dx > params.dy)
		params.err = params.dx / 2;
	else
		params.err = -params.dy / 2;
	while (1)
	{
		mlx_pixel_put(game->mlx_ptr, game->mlx_win, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		draw_line_step(&start, &params);
	}
}

void render_player(t_game *game, t_player *player)
{
    int px = player->x * SIZE;
    int py = player->y * SIZE;
    int color = 0xFF0000;
	int i;
	int j;

	i = 0;
	while (i < SIZE / 3)
	{
		j = 0;
		while (j < SIZE / 3)
		{
			mlx_pixel_put(game->mlx_ptr, game->mlx_win, px + i, py + j, color);
			j++;
		}
		i++;
	}
    int line_length = SIZE / 2;
    int end_x = px + cos(player->angle) * line_length;
    int end_y = py - sin(player->angle) * line_length;
    draw_line(game, (t_point){ .x = px, .y = py}, (t_point){ .x = end_x, .y = end_y} , 0x00FF00); 
}