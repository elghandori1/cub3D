/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:28:40 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 20:41:02 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_ray_direction(t_ray *ray, t_point *stp)
{
	if (ray->angle > PI)
		ray->facing_up = 1;
	else
		ray->facing_up = 0;
	if ((ray->angle <= PI_2 || ray->angle > 3 * PI_2))
		ray->facing_right = 1;
	else
		ray->facing_right = 0;
	stp->x = 1 - 2 * !ray->facing_right;
	stp->y = 1 - 2 * ray->facing_up;
}

t_image	*load_texture(t_game *game, char *path)
{
	t_image	*img;
	int		n;

	img = m_alloc(sizeof(t_image), ALLOC);
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(game->mlx_ptr, \
					path, &img->width, &img->height);
	if (!img->img)
		ft_error(game, "Texture loading failed\n");
	img->addr = mlx_get_data_addr(img->img, &n, &n, &n);
	if (img->addr == NULL)
	{
		return (NULL);
	}
	return (img);
}

void	initialize_textures(t_game *game)
{
	int	i;

	i = 0;
	game->textures[NORTH] = load_texture(game, game->data->no_texture);
	game->textures[SOUTH] = load_texture(game, game->data->so_texture);
	game->textures[WEST] = load_texture(game, game->data->we_texture);
	game->textures[EAST] = load_texture(game, game->data->ea_texture);
	while (++i < 4)
	{
		if (!game->textures[i])
			ft_error(game, "Failed to load textures\n");
	}
}

void	initialize_frame_buffer(t_game *game)
{
	game->frame_buffer.img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->frame_buffer.img)
		ft_error(game, "Frame buffer creation failed\n");
	game->frame_buffer.addr = mlx_get_data_addr(game->frame_buffer.img,
			&game->frame_buffer.bpp, &game->frame_buffer.line_length,
			&game->frame_buffer.endian);
	if (game->frame_buffer.addr == NULL)
		ft_error(game, "Frame buffer creation failed\n");
}

int	wall_hit(double x, double y, t_game *g)
{
	if (x >= 0 && x <= g->data->width * SIZE \
		&& y >= 0 && y <= g->data->height * SIZE)
	{
		if (g->data->square_map[(int)(y / SIZE)][(int)(x / SIZE)] != '1')
			return (1);
	}
	return (0);
}
