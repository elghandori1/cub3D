#include "../cub3D.h"

void	mouse_movement(t_game *game, int old_x)
{
	if (game->mouse.x > old_x)
		game->data->player.angle += (PI / 60);
	else if (game->mouse.x < old_x)
		game->data->player.angle -= (PI / 60);
	if (game->data->player.angle >= 2 * PI)
		game->data->player.angle -= 2 * PI;
	else if (game->data->player.angle < 0)
		game->data->player.angle += 2 * PI;
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	old_x = 0;

	game->mouse.x = x;
	game->mouse.y = y;
	mouse_movement(game, old_x);
	old_x = x;
	return (0);
}
