#include "../../cub3D.h"

void	set_ray_direction(t_ray *ray)
{
	if (ray->angle > PI)
		ray->facing_up = 1;
	else
		ray->facing_up = 0;
	if ((ray->angle <= PI_2 || ray->angle > 3 * PI_2))
		ray->facing_right = 1;
	else
		ray->facing_right = 0;
}

t_image	*load_texture(t_game *game, char *path)
{
	int		n;
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->width,
			&img->height);
	if (!img->img)
		ft_error(game, "Error\nTexture loading failed\n");
	img->addr = mlx_get_data_addr(img->img, &n, &n, &n);
	return (img);
}

void	load_textures(t_game *game)
{
	game->textures[0] = load_texture(game, game->data->no_texture);
	game->textures[1] = load_texture(game, game->data->so_texture);
	game->textures[2] = load_texture(game, game->data->we_texture);
	game->textures[3] = load_texture(game, game->data->ea_texture);
}

void	init_buffer(t_game *g)
{
	g->frame_buffer.img = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	if (!g->frame_buffer.img)
		ft_error(g, "Error\nFrame buffer creation failed\n");
	g->frame_buffer.addr = mlx_get_data_addr(g->frame_buffer.img,
			&g->frame_buffer.bits_per_pixel, &g->frame_buffer.line_length,
			&g->frame_buffer.endian);
}

int	wall_hit(double x, double y, t_game *g)
{

	if (x >= 0 && x <= g->data->width * SIZE && y >= 0 && y <= g->data->height * SIZE)
	{
		if (g->data->square_map[(int)(y / SIZE)][(int)(x / SIZE)] != '1')
			return (1);
	}
	return (0);
}
