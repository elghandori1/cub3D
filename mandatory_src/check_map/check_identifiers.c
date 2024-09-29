/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:20:02 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/29 20:39:37 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_texture_identifiers(t_data *map, char *line, t_game *cub3d)
{
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (map->we)
			ft_error(cub3d, "Duplicate WE identifier\n");
		map->we = 1;
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (map->so)
			ft_error(cub3d, "Duplicate SO identifier\n");
		map->so = 1;
	}
	else if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (map->no)
			ft_error(cub3d, "Duplicate NO identifier\n");
		map->no = 1;
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (map->ea)
			ft_error(cub3d, "Duplicate EA identifier\n");
		map->ea = 1;
	}
}

void	check_color_identifiers(t_data *map, char *line, t_game *cub3d)
{
	if (ft_strncmp(line, "C", 1) == 0)
	{
		if (map->c)
			ft_error(cub3d, "Duplicate C color\n");
		map->c = 1;
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		if (map->f)
			ft_error(cub3d, "Duplicate F color\n");
		map->f = 1;
	}
}

void	validate_identifiers(t_data *map, t_game *cub3d)
{
	if (!map->we || !map->so || !map->no || !map->ea)
		ft_error(cub3d, "Missing texture identifier\n");
	if (!map->c || !map->f)
		ft_error(cub3d, "Missing color identifier\n");
}

void	check_identifier(t_game *content)
{
	int	i;

	i = 0;
	while (content->data->content[i])
	{
		if (ft_strcmp(content->data->content[i], "\n") == 0
			|| ft_strncmp(content->data->content[i], "1", 1) == 0
			|| ft_strncmp(content->data->content[i], "0", 1) == 0)
		{
			i++;
			continue ;
		}
		check_texture_identifiers(content->data, content->data->content[i],
			content);
		check_color_identifiers(content->data, content->data->content[i],
			content);
		i++;
	}
	validate_identifiers(content->data, content);
}
