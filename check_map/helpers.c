#include "../cub3D.h"

void	ft_free(char	**arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int ft_error(char *message)
{
     ft_putstr_fd(message,2);
     exit(EXIT_FAILURE);
}