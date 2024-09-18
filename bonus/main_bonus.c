#include "cub3d_bonus.h"
#include "cute_sound.h"


int	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (-1);
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (free(game->mlx_ptr), -1);
	init_frame_buffer(game);
	load_textures(game);
	game->gun_anim.curr_frame = 0;
	game->gun_anim.totat_frames = 4;
	game->gun_anim.is_shooting = 0;
	game->gun_anim.frame_delay = 20;
	game->gun_anim.frame_counter = 0;
	// cs_init(NULL, 48000, 4096, NULL);
	mlx_mouse_hide(game->mlx_ptr, game->mlx_win); 
	return (0);
}

int		exit_game(void	*param)
{
	// free gc
	// ("quit\n");
	exit(1);
}




void put_gun_to_buffer(t_image *gun, int x, int y, t_game *g)
{
    int i;
	int j;
    int *addr;
	int color;

    addr = (int *)gun->addr;
	j = 0;
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
	if (game->gun_anim.is_shooting == 1)
	{
		game->gun_anim.frame_counter++;
		if (game->gun_anim.frame_counter >= 15)
		{
			game->gun_anim.frame_counter = 0;
			game->gun_anim.curr_frame++;
			if (game->gun_anim.curr_frame >= game->gun_anim.totat_frames)
			{
				game->gun_anim.curr_frame = 0;
				game->gun_anim.is_shooting = 0;
				game->gun_anim.sound_played = 0;
			}
		}
	}
}

int rendering(void *data)
{
	t_game	*game;
	t_ray	ray[WIDTH];

	memset(ray, 0, sizeof(t_ray) * WIDTH);
	game = (t_game *)data;
	move_player(game);
	raycasting(game, ray);
	gun_animation(game);
	cs_sound_params_t door_param;
	door_param = cs_sound_params_default();
	door_param.pitch = 0.15;
	door_param.volume = 1.;
	// if (game->gun_anim.is_shooting && !game->gun_anim.sound_played)
    // {
	// 	cs_play_sound(game->gun_sound, game->params);
	// 	game->gun_anim.sound_played = 1;			
	// }
	// if (game->door_open == 1 && !game->door_sound_played)
	// {
	// 	cs_play_sound(game->door_sound[0], door_param);
	// 	game->door_sound_played = 1;
	// }
	// else if (!game->door_open && !game->door_sound_played)
	// {
	// 	cs_play_sound(game->door_sound[1], door_param);
	// 	game->door_sound_played = 1;
	// }
	minimap(game);
	put_gun_to_buffer(game->gun[game->gun_anim.curr_frame], (WIDTH / 2) - 250 , HEIGHT - 512, game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->frame_buffer.img, 0, 0);
	cs_update(0);
	return (0);
}


int main(int ac, char **av)
{
	static t_game game;
	
	if (ac != 2)
		return (ft_putstr_fd("Error:\nUSAGE:./cub3d /path/to/scean\n", 2), -1);
	check_map(&game, av[1]);
	if (init_game(&game))
		return (EXIT_FAILURE);
	
	// cs_audio_source_t *theme = cs_load_wav("../textures/e1m1.wav", NULL);
	// game.gun_sound = cs_load_wav("../textures/weapon_pistol.wav", NULL);
	// game.door_sound[0] = cs_load_wav("../textures/door_open.wav", NULL);
	// game.door_sound[1] = cs_load_wav("../textures/door_close.wav", NULL);
	// game.door_open = -1;
	// game.params =  cs_sound_params_default();
	// game.params.pitch = 0.55;
	// cs_sound_params_t theme_param;

	// theme_param = cs_sound_params_default();
	// theme_param.looped = true;
	// cs_play_sound(theme, theme_param);

	capture_hooks(&game);
	mlx_loop_hook(game.mlx_ptr, &rendering, &game);
	mlx_loop(game.mlx_ptr);
	
	// cs_free_audio_source(game.gun_sound);
	// cs_free_audio_source(theme);
	// cs_shutdown();
	free_cub3d(&game);
	return (0);
}
