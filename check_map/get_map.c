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

void check_map_last(t_game *cub3d,char **check_last)
{
    int i = 0;
    while (check_last[i])
    {
        if (ft_strncmp(check_last[i], "WE", 2) == 0 || ft_strncmp(check_last[i], "NO", 2) == 0 \
            || ft_strncmp(check_last[i], "EA", 2) == 0 || ft_strncmp(check_last[i], "SO", 2) == 0 \
            || ft_strncmp(check_last[i], "C", 1) == 0 || ft_strncmp(check_last[i], "F", 1) == 0)
            break;
        if (ft_strncmp(check_last[i], "1", 1) == 0 || ft_strncmp(check_last[i], "0", 1) == 0)
            ft_error(cub3d,"the map must be the last !\n");
        i++;
    }
}

void validate_map_borders(t_game *cub3d)
{
     int i,j;
     int rows;
     i=0;
    while (cub3d->map->map[0][i] && cub3d->map->map[0][i] != '\n')
    {
        if (cub3d->map->map[0][i] != '1' && cub3d->map->map[0][i] != ' ')
            ft_error(cub3d, "Error: Map is not surrounded by walls.\n");
         i++;
    }
    i = 0;
    rows = cub3d->map->len - 1;
    while (cub3d->map->map[rows][i] && cub3d->map->map[rows][i] != '\n')
    {
        if (cub3d->map->map[rows][i] != '1' && cub3d->map->map[rows][i] != ' ')
            ft_error(cub3d, "Error: Map is not surrounded by walls.\n");
        i++;
    }
    i = 0;
    while (i < rows)
    {
        if (cub3d->map->map[i][0] != '1' && cub3d->map->map[i][0] != ' ')
            ft_error(cub3d, "Error: Map is not surrounded by walls.\n");
        j = ft_strlen(cub3d->map->map[i]) - 2;
        if (j >= 0 && cub3d->map->map[i][j] != '1' && cub3d->map->map[i][j] != ' ')
            ft_error(cub3d, "Error: Map is not surrounded by walls.\n");
        i++;  
    }
}

void get_map(t_game *cub3d)
{
    int i, j, len;
    int map_start = 0;

    j = 0;
    i = 0;
    cub3d->map->len = map_len(cub3d->map->content);
    len = cub3d->map->len;
    if (len == 0)
        ft_error(cub3d, "Error: the map does not exist!\n");
    cub3d->map->map = malloc((len + 1) * sizeof(char *));
    if (!cub3d->map->map)
        ft_error(cub3d, "Error: Memory allocation failed for map.\n");
    while (cub3d->map->content[i] && !map_start)
    {
        if (ft_search(cub3d->map->content[i][0], "01 "))
            map_start = 1;
        else
            i++;
    }
    while (cub3d->map->content[i])
    {
        cub3d->map->map[j] = ft_strdup(cub3d->map->content[i]);
        if (!cub3d->map->map[j])
            ft_error(cub3d, "Error: Memory allocation failed while copying map.\n");
        i++;
        j++;
    }
    cub3d->map->map[j] = NULL;
    check_map_last(cub3d,cub3d->map->content);
    validate_map_borders(cub3d);
}
