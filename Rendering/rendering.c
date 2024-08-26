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


void draw_player_direction(t_game *game)
{
    t_player *player = &game->map->player;
    float start_x = player->x * SIZE;
    float start_y = player->y * SIZE;
    float end_x = (player->x + player->dir_x * 5) * SIZE;
    float end_y = (player->y + player->dir_y * 5) * SIZE;
    
    float step = 0.001;
    float t = 0;

    while (t <= 0.1)
    {
        int x = start_x + t * (end_x - start_x);
        int y = start_y + t * (end_y - start_y);
        mlx_pixel_put(game->mlx_ptr, game->mlx_win, x, y, 0xFF0000);
        t += step;
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
	draw_player_direction(game);
    // int line_length = SIZE / 2;
    // int end_x = px + cos(player->angle) * line_length;
    // int end_y = py - sin(player->angle) * line_length;
    // draw_line(game, (t_point){ .x = px, .y = py}, (t_point){ .x = end_x, .y = end_y} , 0x00FF00); 
}