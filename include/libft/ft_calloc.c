/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:12:41 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/26 14:54:48 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = m_alloc(count * size, ALLOC);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}
