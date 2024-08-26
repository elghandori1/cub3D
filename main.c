#include "cub3D.h"


t_game  *instance(void)
{
	static  t_game game;

	return (&game);
}
int	window_init(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (-1);
	game->mlx_win = mlx_new_window(game->mlx_ptr, HEIGHT, WIDTH, "cub3D"); // 640x 480 // 1280x960
	if (!game->mlx_win)
		return (-1);
	return (0);
}

int		exit_game()
{
	// free gc
	printf("quit\n");
	exit(1);
}

void	capture_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, 17, 0, exit_game, NULL);
	mlx_hook(game->mlx_win, 2, (1L << 0), game_events, game);
}
t_xpm	*create_image(t_game *game, char *path)
{
	t_xpm	*asset;

	asset = malloc(sizeof(t_xpm));
	if (!asset)
		return (NULL);
	*asset = (t_xpm){0};
	asset->path = path;
	asset->xpm_data = mlx_xpm_file_to_image(game->mlx_ptr, asset->path,
			&asset->width, &asset->height);
	return (asset);
}

int main(int ac, char **av)
{
	t_game *cub3d;
	
	cub3d = NULL;
	if (ac != 2)
		ft_error(cub3d, "Error: Usage: ./cub3d <map_file.cub>\n");
	cub3d = instance();
	check_map(&cub3d, av[1]);
	// RENDERING 
	// TODO : RENDER 2D MAP ON THE SCREEN

	// printf("map H = %d map W = %d\n", cub3d->map->rows, cub3d->map->len);
	// exit(1);
	if (window_init(cub3d))
		return (EXIT_FAILURE);
	
	cub3d->compas = create_image(cub3d, "./textures/compas.xpm");
	render_map(cub3d);
	render_player(cub3d, &cub3d->map->player);
	capture_hooks(cub3d);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->mlx_win, cub3d->compas->xpm_data, 0, 0);
	mlx_loop(cub3d->mlx_ptr);
	free_cub3d(cub3d);
	return 0;
}
