/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:21:22 by sait-alo          #+#    #+#             */
/*   Updated: 2024/10/01 12:10:22 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	key_release(int key, t_game *game)
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

static int	key_press(int keycode, t_game *game)
{
	t_player	*p;

	p = &game->data->player;
	if (keycode == ESC)
		turnoff(game);
	if (keycode == W)
		p->keys.up = 1;
	if (keycode == S)
		p->keys.down = 1;
	if (keycode == A)
		p->keys.left = 1;
	if (keycode == D)
		p->keys.right = 1;
	if (keycode == LEFT)
		p->keys.rot_left = 1;
	if (keycode == RIGHT)
		p->keys.rot_right = 1;
	return (0);
}

void	capture_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, 2, (1L << 0), key_press, game);
	mlx_hook(game->mlx_win, 3, (1L << 1), key_release, game);
	mlx_hook(game->mlx_win, 17, (1L << 17), &turnoff, game);
}
