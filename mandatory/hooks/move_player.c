#include "../../cub3D.h"

int	exit_game(void)
{
	printf("quit\n");
	exit(1);
}

int	key_press(int keycode, t_game *game)
{
	t_player	*p;

	p = &game->data->player;
	if (keycode == ESC)
		exit_game();
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
	mlx_hook(game->mlx_win, 17, (1L << 17), exit_game, NULL);
}
