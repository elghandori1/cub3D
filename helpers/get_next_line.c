/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:46:43 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/29 16:46:47 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mandatory/cub3D.h"

char	*get_next_line(int fd)
{
	char	line[10000];
	char	buffer;
	int		i;
	int		ret;

	i = 0;
	ret = read(fd, &buffer, 1);
	while (ret == 1)
	{
		line[i] = buffer;
		if (line[i++] == '\n')
			break ;
		ret = read(fd, &buffer, 1);
	}
	line[i] = 0;
	if (!line[0])
		return (NULL);
	return (ft_strdup(line));
}
