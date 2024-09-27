#include "cub3D.h"

int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / SIZE);
	map_y = (int)(y / SIZE);
	if (game->data->map[map_y][map_x] == '1' || game->data->map[map_y][(int)((x
				+ WALL_BUFFER * SIZE) / SIZE)] == '1'
		|| game->data->map[map_y][(int)((x - WALL_BUFFER * SIZE) / SIZE)] == '1'
		|| game->data->map[(int)((y + WALL_BUFFER * SIZE) / SIZE)][map_x] == '1'
		|| game->data->map[(int)((y - WALL_BUFFER * SIZE)
			/ SIZE)][map_x] == '1')
		return (0);
	return (1);
}

void	calculate_movement(t_player *p, t_point *move)
{
	move->x = 0;
	move->y = 0;
	if (p->keys.up)
	{
		move->x += p->dir_x * MOVE_SPEED;
		move->y += p->dir_y * MOVE_SPEED;
	}
	if (p->keys.down)
	{
		move->x -= p->dir_x * MOVE_SPEED;
		move->y -= p->dir_y * MOVE_SPEED;
	}
	if (p->keys.left)
	{
		move->x += p->dir_y * MOVE_SPEED;
		move->y -= p->dir_x * MOVE_SPEED;
	}
	if (p->keys.right)
	{
		move->x -= p->dir_y * MOVE_SPEED;
		move->y += p->dir_x * MOVE_SPEED;
	}
}

void	move_player(t_game *game)
{
	t_point		move;
	t_player	*p;

	p = &game->data->player;
	calculate_movement(p, &move);
	if (is_valid_position(game, p->x + move.x, p->y + move.y))
	{
		p->x += move.x;
		p->y += move.y;
	}
	if (p->keys.rot_left)
		p->angle += ROTATION_SPEED;
	if (p->keys.rot_right)
		p->angle -= ROTATION_SPEED;
	p->angle = normalize_angle(p->angle);
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
}
