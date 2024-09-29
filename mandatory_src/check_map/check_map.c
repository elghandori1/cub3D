/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:20:08 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/29 20:43:37 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	has_cub_extension(const char *f_name)
{
	const char	*ext;
	int			len;

	ext = ".cub";
	len = ft_strlen(f_name) - 4;
	return (ft_strncmp(f_name + len, ext, 4) == 0);
}

int	check_empty(char *f_name)
{
	int		fd;
	int		rslt;
	char	buf;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nopen()");
		exit(EXIT_FAILURE);
	}
	rslt = read(fd, &buf, 1);
	close(fd);
	return (rslt);
}

void	check_map(t_game *cub3d, char *file)
{
	if (file)
	{
		if (open(file, __O_DIRECTORY) != -1)
			ft_error(NULL, "This is a directory!\n");
		if (!has_cub_extension(file))
			ft_error(NULL, "Bad extension!\n");
		if (!check_empty(file))
			ft_error(NULL, "Empty file!\n");
		cub3d->data = m_alloc(sizeof(t_data), ALLOC);
		if (!cub3d->data)
			ft_error(NULL, "Memory allocation failed!\n");
		fill_content_data(file, cub3d);
		check_content(cub3d);
	}
	else
		ft_error(NULL, "file not exist!\n");
}
