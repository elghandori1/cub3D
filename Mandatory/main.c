#include "./cub3D.h"

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
int main(int ac, char **av)
{
	static t_game game;
	
	if (ac != 2)
		ft_error(NULL, USAGE);
	check_map(&game, av[1]);
	if (window_init(&game))
		return (EXIT_FAILURE);
	load_textures(&game);
	init_buffer(&game);
	capture_hooks(&game);
	mlx_loop_hook(game.mlx_ptr, &rendering, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
