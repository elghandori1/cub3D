/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:46:50 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/24 23:41:49 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_top_border(t_game *cub3d)
{
	int	idx;

	idx = 0;
	if (!check_row(cub3d->data->map[0]))
	{
		free(cub3d->data->square_map);
		cub3d->data->square_map = NULL;
		ft_error(cub3d, "Error: Map borders are invalid!\n");
	}
	while (cub3d->data->map[0][idx])
	{
		if (ft_search(cub3d->data->map[0][idx], "ENSW"))
		{
            printf("here 1\n");
			free(cub3d->data->square_map);
			cub3d->data->square_map = NULL;
			ft_error(cub3d, "Error: Map borders are invalid!\n");
		}
		idx++;
	}
}

void	check_bottom_border(t_game *cub3d)
{
	int (len), (idx);
	len = cub3d->data->height - 1;
	idx = 0;
	if (!check_row(cub3d->data->map[len]))
	{
		free(cub3d->data->square_map);
		cub3d->data->square_map = NULL;
		ft_error(cub3d, "Error: Map borders are invalid!\n");
	}
	while (cub3d->data->map[len][idx])
	{
		if (ft_search(cub3d->data->map[len][idx], "ENSW"))
		{
			free(cub3d->data->square_map);
			cub3d->data->square_map = NULL;
			ft_error(cub3d, "Error: Map borders are invalid!\n");
		}
		idx++;
	}
}

void	check_top_bottom_borders(t_game *cub3d)
{
	check_top_border(cub3d);
	check_bottom_border(cub3d);
}

void	check_left_right_borders(t_game *cub3d)
{
	int	len;

	int (i), (start), (end);
	len = cub3d->data->height - 1;
	i = 1;
	while (i < len)
	{
		start = 0;
		end = ft_strlen(cub3d->data->map[i]) - 2;
		while (cub3d->data->map[i][start] == ' ')
			start++;
		while (end > start && cub3d->data->map[i][end] == ' ')
			end--;
		if (cub3d->data->map[i][start] != '1'
			|| cub3d->data->map[i][end] != '1')
		{
			free(cub3d->data->square_map);
			cub3d->data->square_map = NULL;
			ft_error(cub3d, "Error: Map borders are invalid!\n");
		}
		i++;
	}
}

void	map_borders(t_game *cub3d)
{
	check_map_height(cub3d);
	check_top_bottom_borders(cub3d);
	check_left_right_borders(cub3d);
}