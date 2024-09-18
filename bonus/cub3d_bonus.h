#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "cute_sound.h"

# define WIDTH  1200 // 1024
# define HEIGHT 700 // 720

# define SIZE 	64
# define PI 	3.14159265358
# define PI_2	1.57079632679489661923
# define PI2	6.28318530718

# define ESC	0xff1b
# define W		0x0077
# define S		0x0073
# define A		0x0061
# define D		0x0064
# define E		0x0065
# define LEFT	65363
# define RIGHT	65361
# define LCTRL 	0xffe3
# define ALLOC	'A'
# define FREE	'F'

#define GRAY_COLOR 0x404040
#define BG_COLOR 0x808080
#define WHITE_COLOR 0xFFFFFF


#define MINIMAP_X_OFFSET 20
#define MINIMAP_Y_OFFSET (HEIGHT - MINIMAP_SIZE * MAP_SCALE - 20)

# define PLAYER_SIZE 0.4
# define PLAYER_COLOR 0xFF0000
# define MOUSE_SENSITIVITY 0.002
//

# define PLAYER_COLOR 0xFF0000
# define FOV_RD 1.04719755119
# define MOVE_SPEED 1
# define ROTATION_SPEED 0.03
# define DISTANCE_PROJ_PLANE ((WIDTH / 2) / tan(FOV_RD / 2))
# define WALL_BUFFER 0.1
# define MAP_SCALE 10
# define MINIMAP_SIZE 15

typedef struct s_minimap
{
    int map_x;
    int map_y;
    int x;
    int y;
} t_minimap;



typedef struct xpm
{
	int			width;
	int			height;
	int			x;
	int			y;
	char		*path;
	void		*img;
	int			*addr;
}				t_xpm;

typedef struct	s_image
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_keys
{
	int up;
	int down;
	int left;
	int right;
	int rot_left;
	int rot_right;
	int open_door;
}	t_keys;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ray
{
	int			id;
	double		angle;
	bool		skip_closed_door;
	char		wall_dir;
	t_point		wall_hit;
	double		distance;
	int			was_hit_vertical;
	int			facing_up;
	int			facing_right;
	unsigned int		wall_strip_height;
	int		wall_top;
	int		wall_bottom;
	char	hit_content;
	char	vhit_content;
	char	hhit_content;
	int		is_door;
}               t_ray;


typedef struct s_player
{
	double		x;
	double		y;
	double 		angle;
	double		dir_x;
	double		dir_y;
	t_keys		keys;
	t_ray		ray;
}	t_player;

typedef struct s_data
{
	int			height;
	int			width;
	char        **content;
	char        **map;
	char        **square_map;
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
} t_data;


typedef	struct s_animation
{
	int curr_frame;
	int totat_frames;
	int is_shooting;
	int frame_delay;
	int frame_counter;
	int sound_played;
}	t_animation;

typedef struct s_mouse
{
    int 	x;
    int 	y;
	bool	show_mouse;
} t_mouse;

typedef struct s_game
{
	t_data		*data;
	t_image   	frame_buffer;
	void		*mlx_ptr;
	void		*mlx_win;
	t_image		*textures[5];
	t_image		*door_texture;
	t_image		*gun[7];
	t_mouse     mouse;
	t_animation	gun_anim;
	cs_audio_source_t *gun_sound;
	cs_audio_source_t *door_sound[2];
	cs_sound_params_t params;
	int		door_open;
	bool door_sound_played;
}   t_game;

/*		Singleton pattern	(Global like)	*/
t_game		*instance(void);



/* 		Raycasting	*/

int		raycasting(t_game *game, t_ray *rays);
void	cast_ray(t_game *g, t_ray *ray);
double	normalize_angle(double angle);
void    move_player(t_game *game);
/*		Rendring		*/
void 	render_wall_strip(t_game *g, t_ray ray);
void	render_map(t_game *game);
void 	render_player(t_game *game, t_player *player);
void	put_pixels(t_image *data, int x, int y, int color);
void minimap(t_game *game);
/*		Hooks	*/
void	capture_hooks(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int key, t_game *game);
int mouse_move(int x, int y, void *param);

void	init_frame_buffer(t_game *g);

/*		Load Textures	*/
void	load_textures(t_game *game);
int		get_color(t_color *color);
int		exit_game();
int		rendering(void	*data);
void    ft_error(t_game *cub3d,char *message);
void    free_map(t_data *map);
void    free_cub3d(t_game *cub3d);
void	ft_free(char	**arr);
int		ft_search(char c, char *set);
int		has_cub_extension(const char *f_name);
int 	check_empty(char *f_name);
void	check_map(t_game *cub3d, char *file);
char	*get_next_line(int fd);
void 	fill_content_data(char *map_file, t_game *cub3d);
void	check_content(t_game *cub3d);
void    initialize_identifiers(t_data *map);
void    check_texture_identifiers(t_data *map, char *line, t_game *cub3d);
void    check_color_identifiers(t_data *map, char *line, t_game *cub3d);
void    validate_identifiers(t_data *map, t_game *cub3d);
void    check_identifier(t_game *content);
void 	check_textures_path(char **content,t_game *cub3d);
void 	get_textures(t_game *cub3d);
char	*get_from_file(char **content, char *target);
void 	get_colors(t_game *cub3d);
void 	get_data(t_game *cub3d);
void	get_square_map(t_game *cub3d);
void    check_map_last(t_game *cub3d,char **check_last);
void	check_player(t_game *cub3d);
int	    check_walls(t_game *cub3d);
#endif