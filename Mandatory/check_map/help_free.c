#include "../cub3D.h"

void	free_textures_res(t_game *game)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (game->textures[i])
			mlx_destroy_image(game->mlx_ptr, game->textures[i]->img);
	}
	if (game->frame_buffer.img)
		mlx_destroy_image(game->mlx_ptr, game->frame_buffer.img);
}

int	turnoff(t_game *game)
{
	if (!game)
		return (exit(0), 0);
	free_textures_res(game);
	m_alloc(0, FREE);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	return (exit(0), 0);
}
