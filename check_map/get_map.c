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

void check_map_last(t_cub3d *cub3d,char **check_last)
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

void	get_square_map(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (cub3d->map->map[i])
	{
		cub3d->map->square_map[i] = malloc(sizeof(char) * cub3d->map->max_len + 1);
		cub3d->map->square_map[i][cub3d->map->max_len] = 0;
		cub3d->map->square_map[i][cub3d->map->max_len - 1] = '\n';
		ft_memset(cub3d->map->square_map[i], 'V', cub3d->map->max_len - 1);
		tmp = 0;
		while (cub3d->map->map[i][j] && cub3d->map->map[i][j] != '\n')
		{
			cub3d->map->square_map[i][j] = cub3d->map->map[i][j];
			j++;
		}
		i++;
		j = 0;
	}
	cub3d->map->square_map[i] = NULL;
}

void get_map(t_cub3d *cub3d)
{
    int i, j, len,map_start;
    
    map_start = 0;
    j = 0;
    i = 0;
    cub3d->map->max_len = 0;
    cub3d->map->len = map_len(cub3d->map->content);
    len = cub3d->map->len + 1;
    if (len == 1)
        ft_error(cub3d, "Error: the map does not exist!\n");
    cub3d->map->map = malloc(len * sizeof(char *));
	cub3d->map->square_map = malloc(len * sizeof(char *));
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
        if (ft_strlen(cub3d->map->map[j]) > cub3d->map->max_len)
			cub3d->map->max_len = ft_strlen(cub3d->map->map[j]);
        i++;
        j++;
    }
    cub3d->map->map[j] = NULL;
	check_map_last(cub3d,cub3d->map->content);
}
