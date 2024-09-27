/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:45:40 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/27 11:38:12 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *theString)
{
	int	i;

	i = 0;
	if (!theString)
		return (0);
	while (theString[i])
	{
		i++;
	}
	return (i);
}
