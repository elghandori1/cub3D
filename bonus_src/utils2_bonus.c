/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:17:13 by sait-alo          #+#    #+#             */
/*   Updated: 2024/09/29 15:59:33 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_gun_to_buffer(t_image *gun, int x, int y, t_game *g)
{
	int	i;
	int	j;	
	int	*addr;	
	int	color;

	j = 0;
	addr = (int *)gun->addr;
	while (j < gun->height)
	{
		i = 0;
		while (i < gun->width)
		{
			color = addr[j * gun->width + i];
			if (color > 0)
				put_pixels(&g->frame_buffer, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	gun_animation(t_game *game)
{
	if (game->gun_anim.is_shooting == true)
	{
		game->gun_anim.frame_counter++;
		if (game->gun_anim.frame_counter >= 10)
		{
			game->gun_anim.frame_counter = 0;
			game->gun_anim.curr_frame++;
			if (game->gun_anim.curr_frame == 4)
			{
				game->gun_anim.curr_frame = 0;
				game->gun_anim.is_shooting = 0;
				game->gun_anim.sound_played = 0;
			}
		}
	}
}

int	gun_fire(int button, int x, int y, void *param)
{
	t_game	*game;

	(void)x;
	(void)y;
	game = (t_game *)param;
	if (button == 1)
	{
		game->gun_anim.is_shooting = 1;
		game->gun_anim.sound_played = 0;
	}
	return (0);
}

void	play_sounds(t_game *game)
{
	if (game->gun_anim.is_shooting && !game->gun_anim.sound_played)
	{
		cs_play_sound(game->audio.gun_sound, game->audio.gun_params);
		game->gun_anim.sound_played = 1;
	}
	if (game->door_open == 1 && !game->door_sound_played)
	{
		cs_play_sound(game->audio.door_sound[0], game->audio.door_params);
		game->door_sound_played = 1;
	}
	else if (!game->door_open && !game->door_sound_played)
	{
		cs_play_sound(game->audio.door_sound[1], game->audio.door_params);
		game->door_sound_played = 1;
	}
}
