
#include "../include/gc.h"
#include "../include/libft/libft.h"

t_gc	*m_new_node(void *ptr)
{
	t_gc	*to_collect;

	to_collect = malloc(sizeof(t_gc));
	if (!to_collect)
		return (NULL);
	to_collect->ptr = ptr;
	to_collect->next = NULL;
	return (to_collect);
}

void	m_free(void *ptr, t_gc **arena)
{
	t_gc	*current;
	t_gc	*prev;

	current = *arena;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*arena = current->next;
			if (current->next)
				current->next->prev = prev;
			free(current->ptr);
			current->ptr = NULL;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	m_add_back(t_gc **lst, t_gc *new)
{
	t_gc	*last;

	if (!lst || !new)
		return (EXIT_FAILURE);
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
	return (EXIT_SUCCESS);
}

void	free_arena(t_gc	**arena)
{
	t_gc	*tmp;

	if (!arena || !*arena)
		return ;
	while (*arena)
	{
		tmp = *arena;
		*arena = (*arena)->next;
		free(tmp->ptr);
		tmp->ptr = NULL;
		free(tmp);
	}
	*arena = NULL;
}

void	*m_alloc(size_t __size, char todo)
{
	static t_gc		*arena = NULL;
	void			*ptr;

	if (todo == FREE)
	{
		free_arena(&arena);
		return (NULL);
	}
	ptr = NULL;
	ptr = malloc(__size);
	if (!ptr || m_add_back(&arena, m_new_node(ptr)))
	{
		if (ptr)
			free(ptr);
		free_arena(&arena);
		write(2, "Memory allocation failed\n", 26);
		exit(EXIT_FAILURE);
	}
	ft_memset(ptr, 0, __size);
	return (ptr);
}
