#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_map
{
	int			rows;
	char		**content;
} t_map;

typedef struct s_cub3d
{
	t_map		*map;
} t_cub3d;

int 	ft_error(char *message);
int		has_cub_extension(const char *f_name);
int 	check_empty(char *f_name);
void 	check_map(t_cub3d **cub3d,char *file);
char	*get_next_line(int fd);
void 	fill_content_map(char *map_file, t_cub3d *cub3d);
void	check_content(t_cub3d *cub3d);

#endif