/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:00:38 by sait-alo          #+#    #+#             */
/*   Updated: 2024/10/01 12:10:53 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_hit_position(t_player *p, int *hit_x, int *hit_y)
{
	int	px1;
	int	px2;

	px1 = p->ray.facing_up;
	px2 = !p->ray.facing_right;
	if (p->ray.was_hit_vertical)
	{
		*hit_x = (int)((p->ray.wall_hit.x - px2) / SIZE);
		*hit_y = (int)(p->ray.wall_hit.y / SIZE);
	}
	else
	{
		*hit_x = (int)(p->ray.wall_hit.x / SIZE);
		*hit_y = (int)((p->ray.wall_hit.y - px1) / SIZE);
	}
}

static void	open_door(t_game *game)
{
	t_player	*p;
	int			hit_x;
	int			hit_y;

	p = &game->data->player;
	p->ray.angle = p->angle;
	p->ray.skip_closed_door = 1;
	cast_ray(game, &p->ray);
	get_hit_position(p, &hit_x, &hit_y);
	if (p->ray.distance < SIZE * 2 && p->ray.hit_content == 'D')
	{
		game->door_sound_played = 0;
		game->door_open = 1;
		game->data->square_map[hit_y][hit_x] = 'd';
	}
	else if (p->ray.distance < SIZE * 2 && p->ray.hit_content == 'd')
	{
		game->door_open = 0;
		game->door_sound_played = 0;
		game->data->square_map[hit_y][hit_x] = 'D';
	}
}

int	key_press(int key, t_game *game)
{
	t_player	*p;

	p = &game->data->player;
	if (key == ESC)
		shutdown2(game);
	if (key == LCTRL)
		control_mouse_status(game);
	if (key == W)
		p->keys.up = 1;
	if (key == S)
		p->keys.down = 1;
	if (key == A)
		p->keys.left = 1;
	if (key == D)
		p->keys.right = 1;
	if (key == LEFT)
		p->keys.rot_left = 1;
	if (key == RIGHT)
		p->keys.rot_right = 1;
	if (key == E)
		open_door(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W)
		game->data->player.keys.up = 0;
	if (key == S)
		game->data->player.keys.down = 0;
	if (key == A)
		game->data->player.keys.left = 0;
	if (key == D)
		game->data->player.keys.right = 0;
	if (key == LEFT)
		game->data->player.keys.rot_left = 0;
	if (key == RIGHT)
		game->data->player.keys.rot_right = 0;
	return (0);
}

void	capture_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->mlx_win, DestroyNotify, \
							StructureNotifyMask, &shutdown2, game);
	mlx_hook(game->mlx_win, MotionNotify, PointerMotionMask, mouse_hook, game);
	mlx_mouse_hook(game->mlx_win, gun_fire, game);
}
