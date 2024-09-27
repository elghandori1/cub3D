#include "cub3d_bonus.h"

void	draw_square(t_image *img, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_SCALE)
	{
		j = 0;
		while (j < MAP_SCALE)
		{
			put_pixels(img, MINIMAP_X_OFFSET + x * MAP_SCALE + j,
				MINIMAP_Y_OFFSET + y * MAP_SCALE + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game, int start_x, int start_y)
{
	t_player	*player;
	float		player_minimap_x;
	float		player_minimap_y;
	float		player_offset;

	int (i), (j);
	player = &game->data->player;
	player_minimap_x = (player->x - start_x * SIZE) / SIZE;
	player_minimap_y = (player->y - start_y * SIZE) / SIZE;
	player_offset = (MAP_SCALE * PLAYER_SIZE) / 2;
	i = 0;
	while (i < MAP_SCALE * PLAYER_SIZE)
	{
		j = 0;
		while (j < MAP_SCALE * PLAYER_SIZE)
		{
			put_pixels(&game->frame_buffer, MINIMAP_X_OFFSET + (player_minimap_x
					* MAP_SCALE - player_offset) + i, MINIMAP_Y_OFFSET
				+ (player_minimap_y * MAP_SCALE - player_offset) + j,
				PLAYER_COLOR);
			j++;
		}
		i++;
	}
}

void	draw_minimap_cell(t_game *game, t_minimap *minimap)
{
	int	color;

	if (minimap->map_x >= 0 && minimap->map_x < game->data->width
		&& minimap->map_y >= 0 && minimap->map_y < game->data->height)
	{
		if (game->data->square_map[minimap->map_y][minimap->map_x] == '1')
			color = 0xFFFFFF;
		else if (game->data->square_map[minimap->map_y][minimap->map_x] == 'R')
			color = 0x880000;
		else if (game->data->square_map[minimap->map_y][minimap->map_x] == 'D')
			color = 0xd13f3f;
		else if (game->data->square_map[minimap->map_y][minimap->map_x] == 'd')
			color = 0x6ad863;
		else if (ft_strchr("V \n", game->data->square_map[minimap->map_y][minimap->map_x]))
			color = 0x404040;
		else
			color = 0x202020;
	}
	else
		color = 0x404040;
	draw_square(&game->frame_buffer, color, minimap->x, minimap->y);
}

void	minimap(t_game *game)
{
	t_player	*player;
	t_minimap	minimap;

	int (start_x), (start_y);
	player = &game->data->player;
	start_x = (player->x / SIZE) - MINIMAP_SIZE / 2;
	start_y = (player->y / SIZE) - MINIMAP_SIZE / 2;
	minimap.y = 1;
	while (minimap.y < MINIMAP_SIZE)
	{
		minimap.x = 1;
		while (minimap.x < MINIMAP_SIZE)
		{
			minimap.map_x = start_x + minimap.x;
			minimap.map_y = start_y + minimap.y;
			draw_minimap_cell(game, &minimap);
			minimap.x++;
		}
		minimap.y++;
	}
	draw_player(game, start_x, start_y);
}
