/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_square_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:48:08 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/24 22:06:14 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_map_height(t_game *cub3d)
{
	int	len;

	len = cub3d->data->height - 1;
	if (len == 0)
	{   
        printf("here 1\n");
		free(cub3d->data->square_map);
		cub3d->data->square_map = NULL;
		ft_error(cub3d, "Error: Map borders are invalid!\n");
	}
}

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
		cub3d->data->square_map[i] = malloc(sizeof(char) * (cub3d->data->width
					+ 1));
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
