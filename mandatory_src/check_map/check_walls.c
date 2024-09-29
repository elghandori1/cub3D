/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:20:20 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/29 14:20:21 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_right(t_game *cub3d, int i, int j)
{
	while (cub3d->data->square_map[i][j])
	{
		if (cub3d->data->square_map[i][j] == '1')
			return (1);
		else if (cub3d->data->square_map[i][j] == ' ')
			return (0);
		j++;
	}
	return (0);
}

int	check_left(t_game *cub3d, int i, int j)
{
	while (j >= 0 && cub3d->data->square_map[i][j])
	{
		if (cub3d->data->square_map[i][j] == '1')
			return (1);
		else if (cub3d->data->square_map[i][j] == ' ')
			return (0);
		j--;
	}
	return (0);
}

int	check_above(t_game *cub3d, int i, int j)
{
	while (i >= 0)
	{
		if (cub3d->data->square_map[i][j] == '1')
			return (1);
		else if (cub3d->data->square_map[i][j] == ' ')
			return (0);
		else if (cub3d->data->square_map[i][j] == 'V')
			break ;
		i--;
	}
	return (0);
}

int	check_bellow(t_game *cub3d, int i, int j)
{
	while (cub3d->data->square_map[i] && cub3d->data->square_map[i][j])
	{
		if (cub3d->data->square_map[i][j] == '1')
			return (1);
		else if (cub3d->data->square_map[i][j] == ' ')
			return (0);
		else if (cub3d->data->square_map[i][j] == 'V')
			break ;
		i++;
	}
	return (0);
}

int	check_walls(t_game *cub3d)
{
	int (i), (j);
	i = 0;
	while (cub3d->data->square_map[i])
	{
		j = 0;
		while (cub3d->data->square_map[i][j])
		{
			if (cub3d->data->square_map[i][j] == '0'
				|| ft_search(cub3d->data->square_map[i][j], "ENSW"))
			{
				if (!check_right(cub3d, i, j + 1))
					return (0);
				if (!check_left(cub3d, i, j - 1))
					return (0);
				if (!check_above(cub3d, i - 1, j))
					return (0);
				if (!check_bellow(cub3d, i + 1, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
