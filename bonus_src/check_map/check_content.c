/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:37:11 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/29 20:51:03 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	valid_content(t_game *cub3d)
{
	int	i;

	i = -1;
	while (cub3d->data->content[++i])
	{
		if (ft_search(cub3d->data->content[i][0], " 01"))
		{
			if (ft_search(cub3d->data->content[i][0], " ")
				&& !ft_strchr(cub3d->data->content[i], '1'))
				ft_error(cub3d, "bad character in content of file\n");
			else
				break ;
		}
		if (ft_search(cub3d->data->content[i][0], "10FC\n"))
			continue ;
		else if (ft_strncmp(cub3d->data->content[i], "WE", 2)
			&& ft_strncmp(cub3d->data->content[i], "NO", 2)
			&& ft_strncmp(cub3d->data->content[i], "EA", 2)
			&& ft_strncmp(cub3d->data->content[i], "SO", 2))
			ft_error(cub3d, "bad character in content of file\n");
	}
}

void	check_content(t_game *cub3d)
{
	if (!check_map_last(cub3d))
	{
		valid_content(cub3d);
		check_identifier(cub3d);
		check_textures_path(cub3d->data->content, cub3d);
		get_textures(cub3d);
		get_colors(cub3d);
		get_map(cub3d);
		get_square_map(cub3d);
		check_player(cub3d);
		if (!check_walls(cub3d))
			ft_error(cub3d, "Map borders are invalid!\n");
	}
	else
		ft_error(cub3d, "The map must be the last!\n");
}
