#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	int			rows;
	char		**content;
	char		*so_texture;
	char		*no_texture;
	char		*ea_texture;
	char		*we_texture;
	char		*f_color;
	char		*c_color;
	t_color		*ciel_color;
	t_color		*floor_color;
} t_map;

typedef struct s_cub3d
{
	t_map		*map;
} t_cub3d;

int 	ft_error(char *message);
void	ft_free(char	**arr);
int		has_cub_extension(const char *f_name);
int 	check_empty(char *f_name);
void 	check_map(t_cub3d **cub3d,char *file);
char	*get_next_line(int fd);
void 	fill_content_map(char *map_file, t_cub3d *cub3d);
void	check_content(t_cub3d *cub3d);
void 	check_textures_path(char **content);
// void 	get_textures(t_cub3d *cub3d);
char	*get_from_file(char **content, char *target);
void 	get_colors(t_cub3d *cub3d);

#endif