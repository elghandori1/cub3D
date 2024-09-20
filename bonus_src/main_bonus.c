#include "cub3d_bonus.h"
#include "cute_sound.h"

void	initialize_window(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		ft_error(NULL, "Failed to init mlx\n"); // to  check if it failes
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (free(game->mlx_ptr), ft_error(NULL, "Failed to init mlx\n"));
}

void	initialize_sound(t_game *game)
{
	cs_init(NULL, 48000, 4096, NULL);
	game->audio.sound_track = cs_load_wav("./resources/e1m1.wav", NULL);
	game->audio.gun_sound = cs_load_wav("./resources/weapon_pistol.wav", NULL);
	game->audio.door_sound[0] = cs_load_wav("./resources/door_open.wav", NULL);
	game->audio.door_sound[1] = cs_load_wav("./resources/door_close.wav", NULL);
	game->door_open = -1;
	game->audio.gun_params =  cs_sound_params_default();
	game->audio.gun_params.pitch = 0.55;
	game->audio.theme_params = cs_sound_params_default();
	game->audio.theme_params.looped = true;
	game->audio.door_params = cs_sound_params_default();
	game->audio.door_params.pitch = 0.15;
	game->audio.door_params.volume = 1;
	cs_play_sound(game->audio.sound_track, game->audio.theme_params);
}

int	init_game(t_game *game)
{
	initialize_window(game);
	initialize_frame(game);
	initialize_textures(game);
	initialize_sound(game);
	mlx_mouse_hide(game->mlx_ptr, game->mlx_win); 
	return (0);
}

int		exit_game(void	*param)
{
	// free gc
	// ("quit\n");
	(void)param;
	exit(1);
}

void	put_gun_to_buffer(t_image *gun, int x, int y, t_game *g)
{
    int i;
	int j;
    int *addr;
	int color;

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
		if (game->gun_anim.frame_counter >= 10) // frame delay
		{
			game->gun_anim.frame_counter = 0;
			game->gun_anim.curr_frame++;
			if (game->gun_anim.curr_frame >= 4)
			{
				game->gun_anim.curr_frame = 0;
				game->gun_anim.is_shooting = 0;
				game->gun_anim.sound_played = 0;
			}
		}
	}
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

int	rendering(void *data)
{
	t_game	*game;
	t_ray	ray[WIDTH];

	game = (t_game *)data;
	memset(ray, 0, sizeof(t_ray) * WIDTH);
	mlx_clear_window(game->mlx_ptr, game->mlx_win);
	move_player(game);
	raycasting(game, ray);
	gun_animation(game);
	play_sounds(game);
	minimap(game);
	put_gun_to_buffer(game->gun[game->gun_anim.curr_frame], (WIDTH / 2) - 256 , (HEIGHT - 512), game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->frame_buffer.img, 0, 0);
	cs_update(0);
	return (0);
}


int main(int ac, char **av)
{
	t_game game;
	
	if (ac != 2)
		ft_error(NULL, USAGE);
	game = (t_game){0};
	check_map(&game, av[1]);
	if (init_game(&game))
		return (EXIT_FAILURE);
	capture_hooks(&game);
	mlx_loop_hook(game.mlx_ptr, &rendering, &game);
	mlx_loop(game.mlx_ptr);
	shutdown(&game);
	return (0);
}
