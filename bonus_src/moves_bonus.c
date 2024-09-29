/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:05:04 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 15:56:07 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_valid_position(t_game *game, double x, double y)
{
	int		map_x;
	int		map_y;
	char	**map;

	map_x = (int)(x / SIZE);
	map_y = (int)(y / SIZE);
	map = game->data->square_map;
	if (ft_strchr("1DR", map[map_y][map_x])
		|| ft_strchr("1DR", map[map_y][(int)((x + WALL_BUFFER * SIZE) / SIZE)])
		|| ft_strchr("1DR", map[map_y][(int)((x - WALL_BUFFER * SIZE) / SIZE)])
		|| ft_strchr("1DR", map[(int)((y + WALL_BUFFER * SIZE) / SIZE)][map_x])
		|| ft_strchr("1DR", map[(int)((y - WALL_BUFFER * SIZE) / SIZE)][map_x]))
		return (0);
	return (1);
}

t_point	calculate_new_position(t_player *p)
{
	t_point		move;

	move = (t_point){0};
	if (p->keys.up)
	{
		move.x += p->dir_x * MOVE_SPEED;
		move.y += p->dir_y * MOVE_SPEED;
	}
	if (p->keys.down)
	{
		move.x -= p->dir_x * MOVE_SPEED;
		move.y -= p->dir_y * MOVE_SPEED;
	}
	if (p->keys.left)
	{
		move.x += p->dir_y * MOVE_SPEED;
		move.y -= p->dir_x * MOVE_SPEED;
	}
	if (p->keys.right)
	{
		move.x -= p->dir_y * MOVE_SPEED;
		move.y += p->dir_x * MOVE_SPEED;
	}
	return (move);
}

void	move_player(t_game *game)
{
	t_player	*p;
	t_point		move;

	p = &game->data->player;
	move = calculate_new_position(p);
	if (is_valid_position(game, p->x + move.x, p->y + move.y))
	{
		p->x += move.x;
		p->y += move.y;
	}
	else if (is_valid_position(game, p->x + move.x, p->y))
		p->x += move.x;
	else if (is_valid_position(game, p->x, p->y + move.y))
		p->y += move.y;
	if (p->keys.rot_left)
		p->angle += ROTATION_SPEED;
	if (p->keys.rot_right)
		p->angle -= ROTATION_SPEED;
	p->angle = normalize_angle(p->angle);
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
}
