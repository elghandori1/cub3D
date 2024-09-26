/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:22:18 by moel-gha          #+#    #+#             */
/*   Updated: 2024/09/26 14:54:58 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)m_alloc(sizeof(t_list), ALLOC);
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
