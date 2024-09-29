/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:04:18 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 12:04:52 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	mouse_movement(t_game *game, int new_x, int new_y)
{
	double	delta_x;
	double	delta_y;

	delta_x = (new_x - ((double)WIDTH / 2)) * MOUSE_SENSITIVITY;
	delta_y = (new_y - ((double)HEIGHT / 2)) * 0.4;
	game->data->player.angle += delta_x;
	game->screen_center -= delta_y;
	if (game->screen_center >= HEIGHT)
		game->screen_center = HEIGHT;
	if (game->screen_center <= 0)
		game->screen_center = 0;
	mlx_mouse_move(game->mlx_ptr, game->mlx_win, (WIDTH / 2), (HEIGHT / 2));
}

int	mouse_hook(int x, int y, void *game)
{
	t_game		*g;
	static int	mouse_mouve = 0;

	g = (t_game *)game;
	mouse_mouve++;
	if (mouse_mouve % 3 == 0 && x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		mouse_mouve = 0;
		if (g->mouse.show_mouse == false)
			mouse_movement(g, x, y);
	}
	return (0);
}

void	control_mouse_status(t_game *game)
{
	if (game->mouse.show_mouse == 0)
		mlx_mouse_show(game->mlx_ptr, game->mlx_win);
	if (game->mouse.show_mouse == 1)
		mlx_mouse_hide(game->mlx_ptr, game->mlx_win);
	game->mouse.show_mouse = !game->mouse.show_mouse;
}
