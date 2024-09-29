/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:40:20 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/29 14:40:21 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	line_counter(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	check_extension_file(char *path, t_game *cub3d)
{
	const char	*ext = ".xpm";
	int			len;

	while (path && *path == ' ')
		path++;
	len = line_counter(path) - 4;
	if (len < 0 || ft_strncmp(path + len, ext, 4) != 0)
		ft_error(cub3d, "Error: Texture file must have .xpm extension\n");
}

void	check_textures_path(char **content, t_game *cub3d)
{
	int		i;
	char	*path;

	i = 0;
	while (content[i])
	{
		if (ft_strncmp(content[i], "WE", 2) == 0 || ft_strncmp(content[i], "SO",
				2) == 0 || ft_strncmp(content[i], "NO", 2) == 0
			|| ft_strncmp(content[i], "EA", 2) == 0)
		{
			path = ft_strchr(content[i], ' ');
			if (path != NULL)
				check_extension_file(path, cub3d);
			else
				ft_error(cub3d, "Error: Missing texture file path\n");
		}
		i++;
	}
}
