#include "../cub3D.h"

void draw_player_direction(t_game *game)
{
	t_player	*player;
	t_point		start;
	t_point		end;
	t_point 	pp;
	double		step;
	double		t;

	t = 0;
	player = &game->data->player;
	start.x = player->x;
	start.y = player->y;
	end.x = (player->x + player->dir_x * 100);
	end.y = (player->y + player->dir_y * 100);
	step = 0.01;
	while (t <= 0.1)
	{
		pp.x = start.x + t * (end.x - start.x);
		pp.y = start.y + t * (end.y - start.y);
		mlx_pixel_put(game->mlx_ptr, game->mlx_win, pp.x, pp.y, 0x90EE90);
		t += step;
	}
}

void render_player(t_game *game, t_player *player)
{
	int px = player->x * (SIZE);
	int py = player->y * (SIZE);
	int color = 0xFF0000;
	int i;
	int j;

	i = 0;
	while (i < SIZE / 4)
	{
		j = 0;
		while (j < SIZE / 4)
		{
			mlx_pixel_put(game->mlx_ptr, game->mlx_win, px + i, py + j, color);
			j++;
		}
		i++;
	}
	draw_player_direction(game);
}