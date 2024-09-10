#include "../cub3D.h"

int is_valid_position(t_game *game, double x, double y)
{
    int map_x = (int)(x / SIZE);
    int map_y = (int)(y / SIZE);
    
    if (game->data->map[map_y][map_x] == '1' ||
        game->data->map[map_y][(int)((x + WALL_BUFFER * SIZE) / SIZE)] == '1' ||
        game->data->map[map_y][(int)((x - WALL_BUFFER * SIZE) / SIZE)] == '1' ||
        game->data->map[(int)((y + WALL_BUFFER * SIZE) / SIZE)][map_x] == '1' ||
        game->data->map[(int)((y - WALL_BUFFER * SIZE) / SIZE)][map_x] == '1')
        return 0;

    return 1;
}

void move_player(t_game *game)
{
    double move_x = 0;
    double move_y = 0;
    t_player *p = &game->data->player;

    if (p->keys.up)
    {
        move_x += p->dir_x * MOVE_SPEED;
        move_y += p->dir_y * MOVE_SPEED;
    }
    if (p->keys.down)
    {
        move_x -= p->dir_x * MOVE_SPEED;
        move_y -= p->dir_y * MOVE_SPEED;
    }
    if (p->keys.left)
    {
        move_x += p->dir_y * MOVE_SPEED;
        move_y -= p->dir_x * MOVE_SPEED;
    }
    if (p->keys.right)
    {
        move_x -= p->dir_y * MOVE_SPEED;
        move_y += p->dir_x * MOVE_SPEED;
    }
    if (is_valid_position(game, p->x + move_x, p->y + move_y))
    {
        p->x += move_x;
        p->y += move_y;
    }
    else if (is_valid_position(game, p->x + move_x, p->y))
        p->x += move_x;
    else if (is_valid_position(game, p->x, p->y + move_y))
        p->y += move_y;
    if (p->keys.rot_left)
        p->angle += ROTATION_SPEED;
    if (p->keys.rot_right)
        p->angle -= ROTATION_SPEED;
    p->angle = normalize_angle(p->angle);
    p->dir_x = cos(p->angle);
    p->dir_y = sin(p->angle);
}

int	game_events(int keycode, t_game *game)
{
    t_player *p;

    p = &game->data->player;
	if (keycode == ESC)
		exit_game();
	else if (keycode == W)
		p->keys.up = 1;
	else if (keycode == S)
		p->keys.down = 1;
	else if (keycode == A)
		p->keys.left = 1;
	else if (keycode == D)
		p->keys.right = 1;
    if (keycode == LEFT)
        p->keys.rot_left = 1;
    else if (keycode == RIGHT)
        p->keys.rot_right = 1;
	return (0);
}
