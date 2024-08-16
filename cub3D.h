#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# define SIZE 64

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_player
{
	int			x;
	int			y;
	float 		angle;
}	t_player;

typedef struct s_map
{
    int         rows;
    char        **content;
    char        **map;
    char        *so_texture;
    char        *no_texture;
    char        *ea_texture;
    char        *we_texture;
    char        *f_color;
    char        *c_color;
    t_color     *ciel_color;
    t_color     *floor_color;
    t_player    player;
    size_t      max_len;
    int         len;
    int         we;
    int         so; 
    int         no; 
    int         ea; 
    int         c; 
    int         f;
} t_map;


typedef struct s_cub3d
{
	t_map		*map;
} t_cub3d;

int 	ft_error(char *message);
void	ft_free(char	**arr);
int		ft_search(char c, char *set);
int		has_cub_extension(const char *f_name);
int 	check_empty(char *f_name);
void 	check_map(t_cub3d **cub3d,char *file);
char	*get_next_line(int fd);
void 	fill_content_map(char *map_file, t_cub3d *cub3d);
void	check_content(t_cub3d *cub3d);
void    initialize_identifiers(t_map *map);
void    check_texture_identifiers(t_map *map, char *line);
void    check_color_identifiers(t_map *map, char *line);
void    validate_identifiers(t_map *map);
void    check_identifier(t_cub3d *content);
void 	check_textures_path(char **content);
void 	get_textures(t_cub3d *cub3d);
char	*get_from_file(char **content, char *target);
void 	get_colors(t_cub3d *cub3d);
void 	get_map(t_cub3d *cub3d);
void    check_map_last(char **check_last);
void	check_player(t_cub3d *cub3d);
#endif