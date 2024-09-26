/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:55:45 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/26 14:53:15 by sait-alo         ###   ########.fr       */
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

void	copy_map(t_game *cub3d, int i)
{
	int j = 0;

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
	int (i), (len), (map_start);
	
	map_start = 0;
	i = 0;
	len = map_len(cub3d->data->content);
	len++;
	if (len == 1)
		ft_error(cub3d, "The map does not exist!\n");
	cub3d->data->map = m_alloc(len * sizeof(char *), ALLOC);
	cub3d->data->square_map = m_alloc(len * sizeof(char *), ALLOC);
	while (cub3d->data->content[i] && !map_start)
	{
		if (ft_search(cub3d->data->content[i][0], "01 "))
			map_start = 1;
		else
			i++;
	}
	copy_map(cub3d, i);
	check_map_last(cub3d, cub3d->data->content);
	map_borders(cub3d);
}