#include "../cub3D.h"

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
    if (map->floor_color)
        free(map->floor_color);
    if (map->ciel_color)
        free(map->ciel_color);
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

void free_cub3d(t_cub3d *cub3d)

{
    if (!cub3d)
        return;
    if (cub3d->map)
    {
        free_map(cub3d->map);
        free(cub3d->map);
    }
    free(cub3d);
}

void ft_error(t_game *cub3d, char *message)
{
    if (cub3d)
        free_cub3d(cub3d);
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
