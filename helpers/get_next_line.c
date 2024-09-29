/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:19:49 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 15:19:50 by sait-alo         ###   ########.fr       */
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
