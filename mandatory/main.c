#include "../cub3D.h"

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
	t_game *game;
	
	if (ac != 2)
		return (ft_putstr_fd("Error:\nToo many args\n", 2), -1);
	game = malloc(sizeof(t_game));
	if (!game)
	{
		perror("Failed to allocate memory for game");
		exit(EXIT_FAILURE);
	}
	check_map(&game, av[1]);
	if (window_init(game))
		return (EXIT_FAILURE);
	
	load_textures(game);
	init_buffer(game);
	capture_hooks(game);
	mlx_loop_hook(game->mlx_ptr, &rendering, game);
	mlx_loop(game->mlx_ptr);
	free_cub3d(game);
	return (0);
}
