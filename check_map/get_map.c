#include "../cub3D.h"

int map_len(char **content)
{
int	i;
	int	len;

	i = 0;
	len = 0;
	while (content[i])
	{
		if (ft_search(content[i][0], "0 1"))
			break ;
		i++;
	}
	while (content[i++])
		len++;
	return (len);
}

void surround_map_with_walls(t_cub3d* cub3d, char **map, int rows)
{
    int i = 0;
    int j;
    while (map[0][i] && map[0][i] != '\n')
    {
        if (map[0][i] != '1' && map[0][i] != ' ')
            ft_error(cub3d, "Error: Map is not surrounded by walls.\n");
        i++;
    }
    i = 0;
    while (map[rows - 1][i] && map[rows - 1][i] != '\n')
    {
        if (map[rows - 1][i] != '1' && map[rows - 1][i] != ' ')
            ft_error(cub3d, "Error: Map is not surrounded by walls.\n");
        i++;
    }
    i = 0;
    while (i < rows)
    {
        if (map[i][0] != '1' && map[i][0] != ' ')
            ft_error(cub3d, "Error: Map is not surrounded by walls.\n");
        j = ft_strlen(map[i]) - 1;
        while (j >= 0 && (map[i][j] == '\0' || map[i][j] == '\n' || map[i][j] == ' '))
            j--;
        if (j >= 0 && map[i][j] != '1' && map[i][j] != ' ')
            ft_error(cub3d, "Error: Map is not surrounded by walls.\n");

        i++;
    }
}


void get_map(t_cub3d *cub3d)
{
    int i, j, len;

    j = 0;
    i = 0;
    cub3d->map->max_len = 0;
    cub3d->map->len = map_len(cub3d->map->content);
    len = cub3d->map->len;
    if (len == 0)
        ft_error(cub3d, "Error: the map does not exist!\n");
    cub3d->map->map = malloc((len + 1) * sizeof(char *));
    if (!cub3d->map->map)
        ft_error(cub3d, "Error: Memory allocation failed for map.\n");
    while (cub3d->map->content[i] && !(cub3d->map->content[i][0] == '1'))
        i++;
    while (cub3d->map->content[i])
    {
        cub3d->map->map[j] = ft_strdup(cub3d->map->content[i]);
        if (ft_strlen(cub3d->map->map[j]) > cub3d->map->max_len)
            cub3d->map->max_len = ft_strlen(cub3d->map->map[j]);
        j++;
        i++;
    }
    cub3d->map->map[j] = NULL;
    surround_map_with_walls(cub3d, cub3d->map->map, j);
}
