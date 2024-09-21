#include "../cub3D.h"
void	destroy_images(t_game *game)
{
	int i = 0;
	
	// mlx_destroy_image()
	printf("width = %d\n", game->textures[0]->width);
	mlx_destroy_image(game->mlx_ptr, game->textures[0]->img);
	mlx_destroy_image(game->mlx_ptr, game->textures[1]->img);
	mlx_destroy_image(game->mlx_ptr, game->textures[2]->img);
	mlx_destroy_image(game->mlx_ptr, game->textures[3]->img);
	mlx_destroy_image(game->mlx_ptr, game->frame_buffer.img);
	free(game->textures[0]);
	free(game->textures[1]);
	free(game->textures[2]);
	free(game->textures[3]);
	// free(game->frame_buffer);
}

void shutdown(t_game *cub3d)
{
    // if (cub3d->mlx_win)
    // // if (cub3d->mlx_ptr)
	// destroy_images(cub3d);
    mlx_destroy_window(cub3d->mlx_ptr ,cub3d->mlx_win);
    mlx_destroy_display(cub3d->mlx_ptr);
    m_alloc(0, FREE);
	// free(cub3d->mlx_ptr);
    // cs_free_audio_source(cub3d->audio.sound_track);
    // cs_free_audio_source(cub3d->audio.gun_sound);
    // cs_free_audio_source(cub3d->audio.door_sound[0]);
    // cs_free_audio_source(cub3d->audio.door_sound[1]);
    // cs_shutdown();
}

int	exit_game(void *param)
{
	t_game *game = (t_game *)param;
	shutdown(game);
	exit(1);
}

int	key_press(int keycode, t_game *game)
{
	t_player	*p;

	p = &game->data->player;
	if (keycode == ESC)
		exit_game(game);
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
