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

void shutdown(t_game *cub3d)
{
    if (cub3d->mlx_ptr)
        mlx_destroy_display(cub3d->mlx_ptr);  
    if (cub3d->mlx_win)
        mlx_destroy_window(cub3d->mlx_ptr ,cub3d->mlx_win);
    if (cub3d->frame_buffer.img)
        mlx_destroy_image(cub3d->mlx_ptr, cub3d->frame_buffer.img);
    if (cub3d->data)
    {
        free_map(cub3d->data);
        free(cub3d->data);
    }
}

void ft_error(t_game *cub3d, char *message)
{
    if (cub3d)
        shutdown(cub3d);
    ft_putstr_fd("Error\n",2);
    ft_putstr_fd(message,2);
    exit(EXIT_FAILURE);
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
