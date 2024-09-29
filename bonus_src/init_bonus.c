/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:01:55 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 15:58:11 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	initialize_window(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		ft_error(game, "Failed to init mlx\n");
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (ft_error(game, "Failed to init mlx win\n"));
}

void	initialize_frame(t_game *g)
{
	g->frame_buffer.img = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	if (!g->frame_buffer.img)
		ft_error(g, "Frame buffer creation failed\n");
	g->frame_buffer.addr = mlx_get_data_addr(g->frame_buffer.img, \
											&g->frame_buffer.bpp, \
											&g->frame_buffer.line_length, \
											&g->frame_buffer.endian);
	if (!g->frame_buffer.addr)
		return (ft_error(g, "Failed to get data addr\n"));
}

void	initialize_sound(t_game *game)
{
	if (cs_init(NULL, 48000, 4096, NULL))
		return (ft_error(game, "Failed to init cs context\n"));
	game->audio.sound_track = cs_load_wav("./resources/e1m1.wav", NULL);
	if (!game->audio.sound_track)
		return (ft_error(game, "Failed to load audio.sound_track\n"));
	game->audio.gun_sound = cs_load_wav("./resources/weapon_pistol.wav", NULL);
	if (!game->audio.gun_sound)
		return (ft_error(game, "Failed to load audio.gun_sound\n"));
	game->audio.door_sound[0] = cs_load_wav("./resources/door_open.wav", NULL);
	if (!game->audio.door_sound[0])
		return (ft_error(game, "Failed to load audio.door_sound[0]\n"));
	game->audio.door_sound[1] = cs_load_wav("./resources/door_close.wav", NULL);
	if (!game->audio.door_sound[1])
		return (ft_error(game, "Failed to load audio.door_sound[1]\n"));
	game->door_open = -1;
	game->audio.gun_params = cs_sound_params_default();
	game->audio.gun_params.pitch = 0.55;
	game->audio.theme_params = cs_sound_params_default();
	game->audio.theme_params.looped = true;
	game->audio.door_params = cs_sound_params_default();
	game->audio.door_params.pitch = 0.15;
	game->audio.door_params.volume = 1;
	cs_play_sound(game->audio.sound_track, game->audio.theme_params);
}

static t_image	*load_texture(t_game *game, char *path)
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

	i = -1;
	game->textures[NORTH] = load_texture(game, game->data->no_texture);
	game->textures[SOUTH] = load_texture(game, game->data->so_texture);
	game->textures[WEST] = load_texture(game, game->data->we_texture);
	game->textures[EAST] = load_texture(game, game->data->ea_texture);
	game->textures[SHOOT_BOARD] = load_texture(game, SHOOT_BOARD_PATH);
	game->textures[DOOR] = load_texture(game, "./resources/door.xpm");
	while (++i < 6)
	{
		if (!game->textures[i])
			ft_error(game, "Failed to load textures\n");
	}
	game->gun[0] = load_texture(game, "./resources/pis-0.xpm");
	game->gun[1] = load_texture(game, "./resources/pis-1.xpm");
	game->gun[2] = load_texture(game, "./resources/pis-2.xpm");
	game->gun[3] = load_texture(game, "./resources/pis-3.xpm");
	i = -1;
	while (++i < 4)
	{
		if (!game->gun[i])
			ft_error(game, "Failed to load textures\n");
	}
}
