#include "cub3D.h"

t_game	*game_instance(void)
{
	static t_game	game;

	return (&game);
}

int rendering(void *data)
{
	t_game	*game;
	t_ray	ray[WIDTH];

	game = (t_game *)data;
	move_player(game);
	raycasting(game, ray);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->frame_buffer.img, 0, 0);
	return (0);
}
int	main(int ac, char **av)
{
	t_game *game;
	
	if (ac != 2)
		return (ft_putstr_fd("Error:\nUSAGE:./cub3d maps/*.cub\n", 2), EXIT_FAILURE);
	game = game_instance();
	check_map(game, av[1]);
	if (window_init(game))
		return (EXIT_FAILURE);
	load_textures(game);
	init_buffer(game);
	capture_hooks(game);
	mlx_loop_hook(game->mlx_ptr, &rendering, game);
	mlx_loop(game->mlx_ptr);
	// shutdown(game);
	return (0);
}
