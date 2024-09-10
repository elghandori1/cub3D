#include "../cub3D.h"

void draw_player_direction(t_game *game, t_player *player)
{
	t_point		start;
	t_point		end;
	t_point 	pp;
	double		step;
	double		t;
	t_point		p;

	t = 0;
	p.x = player->x / SIZE;
	p.y = player->y / SIZE;
	start.x = (p.x * MAP_SCALE) + MAP_SCALE / 4;
	start.y = (p.y * MAP_SCALE) + MAP_SCALE / 4;
	end.x = (start.x + player->dir_x * 100);
	end.y = (start.y + player->dir_y * 100);
	step = 0.01;
	while (t <= 0.1)
	{
		pp.x = start.x + t * (end.x - start.x);
		pp.y = start.y + t * (end.y - start.y);
		my_mlx_pixel_put(&game->frame_buffer, pp.x, pp.y, PLAYER_COLOR);
		t += step;
	}	
}

void render_player(t_game *game, t_player *player)
{
	int 	i;
	int 	j;
	t_point p;

	p.x = player->x / SIZE;
	p.y = player->y / SIZE;
	i = 0;
	while (i < MAP_SCALE / 2)
	{
		j = 0;
		while (j < MAP_SCALE / 2)
		{
			my_mlx_pixel_put(&game->frame_buffer, p.x * MAP_SCALE + i, p.y * MAP_SCALE + j, PLAYER_COLOR);
			j++;
		}
		i++;
	}
	draw_player_direction(game, player);
}