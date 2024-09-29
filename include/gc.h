/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:20:19 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 15:20:27 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# define ALLOC	'A'
# define FREE	'F'

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
	struct s_gc	*prev;
}				t_gc;

void				*m_alloc(size_t __size, char todo);

#endif