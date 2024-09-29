/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:20:47 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 15:21:02 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

static int	rendering(t_game *game)
{
	move_player(game);
	raycasting(game, game->ray);
	mlx_put_image_to_window(game->mlx_ptr, \
							game->mlx_win, \
							game->frame_buffer.img, 0, 0);
	return (0);
}

static void	initialize_game(t_game *game)
{
	initialize_window(game);
	initialize_textures(game);
	initialize_frame_buffer(game);
}

int	main(int ac, char **av)
{
	static t_game	game;

	if (ac != 2)
		return (ft_putstr_fd(USAGE, 2), EXIT_FAILURE);
	check_map(&game, av[1]);
	initialize_game(&game);
	capture_hooks(&game);
	mlx_loop_hook(game.mlx_ptr, &rendering, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
