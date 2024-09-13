#include "../cub3D.h"

void draw_square(t_image *img, int color, int x, int y)
{
    int i = 0;
    int j;

    while (i < MAP_SCALE)
    {
        j = 0;
        while (j < MAP_SCALE)
        {
            my_mlx_pixel_put(img, x * MAP_SCALE + j, y * MAP_SCALE + i, color);
            j++;
        }
        i++;
    }
}

void draw_player(t_game *game, int start_x, int start_y)
{
    t_player *player = &game->data->player;
    float player_minimap_x = (player->x - start_x * SIZE) / SIZE;
    float player_minimap_y = (player->y - start_y * SIZE) / SIZE;
    float player_offset = (MAP_SCALE * PLAYER_SIZE) / 2;
    
    int i = 0;
    while (i < MAP_SCALE * PLAYER_SIZE)
    {
        int j = 0;
        while (j < MAP_SCALE * PLAYER_SIZE)
        {
            my_mlx_pixel_put(&game->frame_buffer,
                             (player_minimap_x * MAP_SCALE - player_offset) + i,
                             (player_minimap_y * MAP_SCALE - player_offset) + j,
                             PLAYER_COLOR);
            j++;
        }
        i++;
    }
}

void minimap(t_game *game)
{
    int x, y;
    int color;
    int map_x, map_y;
    int start_x, start_y;
    t_player *player = &game->data->player;

    start_x = (player->x / SIZE) - MINIMAP_SIZE / 2;
    start_y = (player->y / SIZE) - MINIMAP_SIZE / 2;

    y = 0;
    while (y < MINIMAP_SIZE)
    {
        x = 0;
        while (x < MINIMAP_SIZE)
        {
            map_x = start_x + x;
            map_y = start_y + y;

            if (map_x >= 0 && map_x < game->data->width && map_y >= 0 && map_y < game->data->height)
            {
                if (game->data->map[map_y][map_x] == '1')
                    color = 0xFFFFFF;
                else
                    color = GRAY_COLOR;
            }
            else
                color = 0x404040;
            draw_square(&game->frame_buffer, color, x, y);
            x++;
        }
        y++;
    }
    draw_player(game, start_x, start_y);
}
