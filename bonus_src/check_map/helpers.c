#include "../cub3d_bonus.h"


void    free_sound_resources(t_game *game)
{
    if (game->audio.sound_track)
    {
        cs_stop_all_playing_sounds();
        if (game->audio.door_sound[0])
            cs_free_audio_source(game->audio.door_sound[0]);
        if (game->audio.door_sound[1])
            cs_free_audio_source(game->audio.door_sound[1]);
        if (game->audio.gun_sound)
            cs_free_audio_source(game->audio.gun_sound);
        cs_free_audio_source(game->audio.sound_track);
        cs_shutdown();
        SDL_Quit();
    }
}
void    free_textures_resources(t_game *game)
{
    int i;

    i = -1;
    while (++i < 6)
    {
        if (game->textures[i])
             mlx_destroy_image(game->mlx_ptr, game->textures[i]->img);
    }
    i = -1;
    while (++i < 4)
    {
        if (game->gun[i])
            mlx_destroy_image(game->mlx_ptr, game->gun[i]->img);
    }
    if (game->frame_buffer.img)
	    mlx_destroy_image(game->mlx_ptr, game->frame_buffer.img);
}

int    shutdown2(t_game *game)
{
    if (!game)
        return (exit(0), 0);
    free_textures_resources(game);
    free_sound_resources(game);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	if (game->mlx_ptr)
    {
        mlx_destroy_display(game->mlx_ptr);
	    free(game->mlx_ptr);
    }
    m_alloc(0, FREE);
    return (exit(0), 0);
}

void    ft_error(t_game *cub3d, char *message)
{
    ft_putstr_fd(message,2);
    shutdown2(cub3d);
}

int	ft_search(char c, char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}
