/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:46:43 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/29 18:00:39 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory_src/cub3D.h"

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
