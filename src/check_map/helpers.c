#include "../../cub3D.h"

void	ft_free(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	ft_error(t_game *cub3d, char *message)
{
	if (cub3d)
		free_cub3d(cub3d);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

int	ft_search(char c, char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}
