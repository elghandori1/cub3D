#include "../cub3D.h"

void draw_player_direction(t_game *game, t_player *player)
{
	t_point		start;
	t_point		end;
	t_point 	pp;
	double		step;
	double		t;

	t = 0;
	int px, py;
	px = player->x / SIZE;
	py = player->y / SIZE;
	start.x = px * MAP_SCALE;
	start.y = py * MAP_SCALE;
	end.x = (px + player->dir_x * 100);
	end.y = (py + player->dir_y * 100);
	step = 0.01;
	while (t <= 0.1)
	{
		pp.x = start.x + t * (end.x - start.x);
		pp.y = start.y + t * (end.y - start.y);
		my_mlx_pixel_put(&game->frame_buffer, pp.x, pp.y, 0x90EE90);
		t += step;
	}
	
}

void render_player(t_game *game, t_player *player)
{
	int px = player->x / SIZE;
	int py = player->y / SIZE;
	int color = 0xFF0000;
	int i;
	int j;

	i = 0;
	while (i < MAP_SCALE / 2)
	{
		j = 0;
		while (j < MAP_SCALE / 2)
		{
			my_mlx_pixel_put(&game->frame_buffer, px * MAP_SCALE + i, py * MAP_SCALE + j, color);
			j++;
		}
		i++;
	}
	draw_player_direction(game, player);
}