#include "../cub3D.h"

int	check_row(char *row)
{
	int	start;
	int	end;

	start = 0;
	while (row[start] == ' ')
		start++;
	end = ft_strlen(row) - 1;
	while (end > start && (row[end] == ' ' || row[end] == '\n'))
		end--;
	if (row[start] != '1' || row[end] != '1')
		return (0);
	return (1);
}

int	map_len(char **content)
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

void check_newline(t_game *cub3d, int i, int len)
{
    if (cub3d->data->map[i][0] == '\n')
	{
        ft_error(cub3d, "invalid map (extra new line)!\n");
	}
    if (i == len - 1 && cub3d->data->map[i][ft_strlen(cub3d->data->map[i]) - 1] == '\n')
	{
        ft_error(cub3d, "invalid map (extra new line at the end of the map)!\n");
	}
}

void copy_map(t_game *cub3d, int i)
{
    int j,k;
	j = 0;
    while (cub3d->data->content[i])
    {
        cub3d->data->map[j] = ft_strdup(cub3d->data->content[i]);
        if (ft_strlen(cub3d->data->map[j]) > (size_t)cub3d->data->width)
            cub3d->data->width = ft_strlen(cub3d->data->map[j]);
        i++;
        j++;
    }
    cub3d->data->map[j] = NULL;
    cub3d->data->height = j;
    k = 0;
    while (k < j)
    {
        check_newline(cub3d, k, j);
        k++;
    }
}

void	get_map(t_game *cub3d)
{
	int (i), (len), (map_start);
	
	map_start = 0;
	i = 0;
	len = map_len(cub3d->data->content);
	len++;
	if (len == 1)
		ft_error(cub3d, "The map does not exist!\n");
	cub3d->data->map = m_alloc(len * sizeof(char *), ALLOC);
	cub3d->data->square_map = m_alloc(len * sizeof(char *), ALLOC);
	while (cub3d->data->content[i] && !ft_search(cub3d->data->content[i][0], "0 1"))
		i++;
	copy_map(cub3d, i);
	map_borders(cub3d);
}
