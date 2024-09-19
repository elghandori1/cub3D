/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:55:45 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/18 22:34:59 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void	check_map_last(t_game *cub3d, char **check_last)
{
	int	i;

	i = 0;
	while (check_last[i])
	{
		if (ft_strncmp(check_last[i], "WE", 2) == 0 || ft_strncmp(check_last[i],
				"NO", 2) == 0 || ft_strncmp(check_last[i], "EA", 2) == 0
			|| ft_strncmp(check_last[i], "SO", 2) == 0
			|| ft_strncmp(check_last[i], "C", 1) == 0
			|| ft_strncmp(check_last[i], "F", 1) == 0)
			break ;
		if (ft_strncmp(check_last[i], "1", 1) == 0 || ft_strncmp(check_last[i],
				"0", 1) == 0)
			ft_error(cub3d, "the map must be the last !\n");
		i++;
	}
}

void	get_square_map(t_game *cub3d)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (cub3d->data->map[i])
	{
		cub3d->data->square_map[i] = malloc(sizeof(char) * (cub3d->data->width + 1));
		cub3d->data->square_map[i][cub3d->data->width] = 0;
		cub3d->data->square_map[i][cub3d->data->width - 1] = '\n';
		ft_memset(cub3d->data->square_map[i], 'V', cub3d->data->width - 1);
		tmp = 0;
		while (cub3d->data->map[i][j] && cub3d->data->map[i][j] != '\n')
		{
   			cub3d->data->square_map[i][j] = cub3d->data->map[i][j];
    		j++;
		}
		i++;
		j = 0;
	}
	cub3d->data->square_map[i] = NULL;
}

void	copy_map(t_game *cub3d, int i, int j, int len1)
{
	while (cub3d->data->content[i])
	{
		cub3d->data->map[j] = ft_strdup(cub3d->data->content[i]);
		if (ft_strlen(cub3d->data->map[j]) > cub3d->data->width)
			cub3d->data->width = ft_strlen(cub3d->data->map[j]);
		i++;
		j++;
	}
	cub3d->data->map[j] = NULL;
	cub3d->data->height = j;
}

void	get_data(t_game *cub3d)
{
	int (i), (j), (len), (map_start);
	
	map_start = 0;
	j = 0;
	i = 0;
	len = map_len(cub3d->data->content);
	len++;
	if (len == 1)
		ft_error(cub3d, " the map does not exist!\n");
	cub3d->data->map = malloc(len * sizeof(char *));
	cub3d->data->square_map = malloc(len * sizeof(char *));
	while (cub3d->data->content[i] && !map_start)
	{
		if (ft_search(cub3d->data->content[i][0], "01 "))
			map_start = 1;
		else
			i++;
	}
	copy_map(cub3d, i, j, len);
	check_map_last(cub3d, cub3d->data->content);
}
