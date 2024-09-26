#ifndef GC_H
#define GC_H

# define ALLOC	'A'
# define FREE	'F'

#include <stdlib.h>
#include <unistd.h>


typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
	struct s_gc	*prev;
}				t_gc;

void				*m_alloc(size_t __size, char todo);

#endif