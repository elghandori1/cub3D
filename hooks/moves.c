#include "../cub3D.h"

int is_valid_position(t_game *game, int x, int y)
{
    return (game->data->map[(y / SIZE)][(x / SIZE)] != '1');
}

void move_player_up(t_game *game)
{
    double new_x = game->data->player.x + game->data->player.dir_x * MOVE_SPEED;
    double new_y = game->data->player.y + game->data->player.dir_y * MOVE_SPEED;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->data->player.x = new_x;
        game->data->player.y = new_y;
    }
}

void move_player_down(t_game *game)
{
    double new_x = game->data->player.x - game->data->player.dir_x * MOVE_SPEED;
    double new_y = game->data->player.y - game->data->player.dir_y * MOVE_SPEED;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->data->player.x = new_x;
        game->data->player.y = new_y;
    }
}

void move_player_right(t_game *game)
{
    double perpendicular_x = -game->data->player.dir_y;
    double perpendicular_y = game->data->player.dir_x;
    double new_x = game->data->player.x + perpendicular_x * MOVE_SPEED;
    double new_y = game->data->player.y + perpendicular_y * MOVE_SPEED;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->data->player.x = new_x;
        game->data->player.y = new_y;
    }
}

void move_player_left(t_game *game)
{
	
    double perpendicular_x = game->data->player.dir_y;
    double perpendicular_y = -game->data->player.dir_x;
    double new_x = game->data->player.x + perpendicular_x * MOVE_SPEED;
    double new_y = game->data->player.y + perpendicular_y * MOVE_SPEED;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->data->player.x = new_x;
        game->data->player.y = new_y;
    }
}

void rotate_player_right(t_game *game)
{
    game->data->player.angle -= ROTATION_SPEED;
    if (game->data->player.angle < 0)
        game->data->player.angle += 2 * PI;
}

void rotate_player_left(t_game *game)
{	
    game->data->player.angle += ROTATION_SPEED;
	if (game->data->player.angle > 2 * PI)
		game->data->player.angle -= 2 * PI;
}
void    move_player(t_game *game)
{
    t_player *p;

    p = &game->data->player;
    if (p->keys.up)
        move_player_up(game);
    if (p->keys.down)
        move_player_down(game);
    if (p->keys.left)
        move_player_left(game);
    if (p->keys.right)
        move_player_right(game);
    if (p->keys.rot_left)
        p->angle += ROTATION_SPEED;
    if (p->keys.rot_right)
        p->angle -= ROTATION_SPEED;
    normalize_angle(p->angle); 
    game->data->player.dir_x = cos(game->data->player.angle);
    game->data->player.dir_y = sin(game->data->player.angle);
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
