#include "../cub3D.h"

int is_valid_position(t_game *game, int x, int y)
{
    return (x >= 0 && x < ft_strlen(game->map->map[0])
		&& y >= 0 && y < game->map->len && game->map->map[y][x] != '1');
}

void move_player_up(t_game *game)
{
    float new_x = game->map->player.x + game->map->player.dir_x * 0.2;
    float new_y = game->map->player.y + game->map->player.dir_y * 0.2;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        render_map(game);
        render_player(game, &game->map->player);
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->compas->xpm_data, 0, 0);
    }
}

void move_player_down(t_game *game)
{
    float new_x = game->map->player.x - game->map->player.dir_x * 0.2;
    float new_y = game->map->player.y - game->map->player.dir_y * 0.2;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        render_map(game);
        render_player(game, &game->map->player);
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->compas->xpm_data, 0, 0);
    }
}

void move_player_right(t_game *game)
{
    float perpendicular_x = -game->map->player.dir_y;
    float perpendicular_y = game->map->player.dir_x;
    float new_x = game->map->player.x + perpendicular_x * 0.2;
    float new_y = game->map->player.y + perpendicular_y * 0.2;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        render_map(game);
        render_player(game, &game->map->player);
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->compas->xpm_data, 0, 0);
    }
}

void move_player_left(t_game *game)
{
	
    float perpendicular_x = game->map->player.dir_y;
    float perpendicular_y = -game->map->player.dir_x;
    float new_x = game->map->player.x + perpendicular_x * 0.2;
    float new_y = game->map->player.y + perpendicular_y * 0.2;
    
    if (is_valid_position(game, (int)new_x, (int)new_y))
    {
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        render_map(game);
        render_player(game, &game->map->player);
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->compas->xpm_data, 0, 0);
    }
}

void rotate_player_left(t_game *game)
{
    game->map->player.angle -= .05;
    if (game->map->player.angle < 0)
        game->map->player.angle += 2 * PI;
    game->map->player.dir_x = cos(game->map->player.angle);
    game->map->player.dir_y = -sin(game->map->player.angle);
    render_map(game);
    render_player(game, &game->map->player);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->compas->xpm_data, 0, 0);
}

void rotate_player_right(t_game *game)
{	
    game->map->player.angle += .05;
	if (game->map->player.angle > 2 * PI)
		game->map->player.angle -= 2 * PI;
    game->map->player.dir_x = cos(game->map->player.angle);
    game->map->player.dir_y = -sin(game->map->player.angle);
    render_map(game);
    render_player(game, &game->map->player);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->compas->xpm_data, 0, 0);
}


int	game_events(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game();
	else if (keycode == W)
		move_player_up(game);
	else if (keycode == S)
		move_player_down(game);
	else if (keycode == A)
		move_player_left(game);
	else if (keycode == D)
		move_player_right(game);
    else if (keycode == LEFT)
        rotate_player_left(game);
    else if (keycode == RIGHT)
        rotate_player_right(game);
	return (0);
}