#include "../cub3d_bonus.h"

void	ft_free(char	**arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void free_map(t_data *map)
{
    int i;

    if (!map)
        return;
    if (map->content)
    {
        i = 0;
        while (map->content[i])
            free(map->content[i++]);
        free(map->content);
    }
    if (map->so_texture)
        free(map->so_texture);
    if (map->no_texture)
        free(map->no_texture);
    if (map->ea_texture)
        free(map->ea_texture);
    if (map->we_texture)
        free(map->we_texture);

    if (map->c_color)
        free(map->c_color);
    if (map->f_color)
        free(map->f_color);

    if (map->map && map->square_map)
    {
        i = 0;
        while (i < map->len)
        {
            free(map->map[i]);
            free(map->square_map[i]);
            i++;
        }
        free(map->map);
        free(map->square_map);
    }
}
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
    ft_putstr_fd("Error\n",2);
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
