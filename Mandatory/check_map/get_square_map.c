/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_square_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:48:08 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/27 10:58:32 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	get_square_map(t_game *cub3d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub3d->data->map[i])
	{
		cub3d->data->square_map[i] = m_alloc(sizeof(char) * (cub3d->data->width + 1), ALLOC);
		cub3d->data->square_map[i][cub3d->data->width] = 0;
		cub3d->data->square_map[i][cub3d->data->width - 1] = '\n';
		ft_memset(cub3d->data->square_map[i], 'V', cub3d->data->width - 1);
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
