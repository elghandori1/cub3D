/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:59:11 by sait-alo          #+#    #+#             */
/*   Updated: 2024/10/01 12:09:21 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	rendering(t_game *game)
{
	move_player(game);
	raycasting(game, game->ray);
	gun_animation(game);
	play_sounds(game);
	minimap(game);
	put_gun_to_buffer(game->gun[game->gun_anim.curr_frame], \
					(WIDTH / 2) - 256, \
					(HEIGHT - 512), game);
	mlx_put_image_to_window(game->mlx_ptr, \
							game->mlx_win, \
							game->frame_buffer.img, 0, 0);
	cs_update(0);
	return (0);
}

void	init_game(t_game *game)
{
	initialize_window(game);
	initialize_frame(game);
	initialize_textures(game);
	initialize_sound(game);
	mlx_mouse_move(game->mlx_ptr, game->mlx_win, (WIDTH / 2), (HEIGHT / 2));
	mlx_mouse_hide(game->mlx_ptr, game->mlx_win);
	game->screen_center = HEIGHT / 2;
}

int	main(int ac, char **av)
{
	static t_game	game;

	if (ac != 2)
		ft_error(NULL, USAGE);
	check_map(&game, av[1]);
	init_game(&game);
	capture_hooks(&game);
	mlx_loop_hook(game.mlx_ptr, &rendering, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
