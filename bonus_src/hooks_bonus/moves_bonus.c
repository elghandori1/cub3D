#include "../cub3d_bonus.h"

void	open_door(t_game *game);

int is_valid_position(t_game *game, double x, double y)
{
	int		map_x;
	int		map_y;
	char	**map;

	map_x = (int)(x / SIZE);
	map_y = (int)(y / SIZE);
	map = game->data->square_map;
	if (ft_strchr("1DR", map[map_y][map_x])
		|| ft_strchr("1DR", map[map_y][(int)((x + WALL_BUFFER * SIZE) / SIZE)])
		|| ft_strchr("1DR", map[map_y][(int)((x - WALL_BUFFER * SIZE) / SIZE)])
		|| ft_strchr("1DR", map[(int)((y + WALL_BUFFER * SIZE) / SIZE)][map_x])
		|| ft_strchr("1DR", map[(int)((y - WALL_BUFFER * SIZE) / SIZE)][map_x]))
		return (0);
	return (1);
}
t_point	calculate_new_position(t_player *p)
{
	t_point		move;

	move = (t_point){0};
	if (p->keys.up)
	{
		move.x += p->dir_x * MOVE_SPEED;
		move.y += p->dir_y * MOVE_SPEED;
	}
	if (p->keys.down)
	{
		move.x -= p->dir_x * MOVE_SPEED;
		move.y -= p->dir_y * MOVE_SPEED;
	}
	if (p->keys.left)
	{
		move.x += p->dir_y * MOVE_SPEED;
		move.y -= p->dir_x * MOVE_SPEED;
	}
	if (p->keys.right)
	{
		move.x -= p->dir_y * MOVE_SPEED;
		move.y += p->dir_x * MOVE_SPEED;
	}
	return (move);
}

void	move_player(t_game *game)
{
	t_player	*p;
	t_point		move;

	p = &game->data->player;
	move = calculate_new_position(p);
	if (is_valid_position(game, p->x + move.x, p->y + move.y))
	{
		p->x += move.x;
		p->y += move.y;
	}
	else if (is_valid_position(game, p->x + move.x, p->y))
		p->x += move.x;
	else if (is_valid_position(game, p->x, p->y + move.y))
		p->y += move.y;
	if (p->keys.rot_left)
		p->angle += ROTATION_SPEED;
	if (p->keys.rot_right)
		p->angle -= ROTATION_SPEED;
	p->angle = normalize_angle(p->angle);
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
}

int		key_release(int key, t_game *game)
{
	if (key == W)
		game->data->player.keys.up = 0;
	if (key == S)
		game->data->player.keys.down = 0;
	if (key == A)
		game->data->player.keys.left = 0;
	if (key == D)
		game->data->player.keys.right = 0;
	if (key == LEFT)
		game->data->player.keys.rot_left = 0;
	if (key == RIGHT)
		game->data->player.keys.rot_right = 0;
	return (0);
}

void	open_door(t_game *game)
{
	t_player *p;
	int map_x;
	int map_y;

	p = &game->data->player;
	p->ray.angle = p->angle;
	p->ray.skip_closed_door = 1;
	cast_ray(game, &p->ray);
	int pixel = 1 - 2 * !p->ray.facing_up;
	int pixel2 = 1 - 2 * p->ray.facing_right;
	if (p->ray.was_hit_vertical)
	{
		map_x = (int)((p->ray.wall_hit.x - pixel2) / SIZE);
		map_y = (int)(p->ray.wall_hit.y / SIZE);
	}
	else
	{
		map_x = (int)(p->ray.wall_hit.x / SIZE);
		map_y = (int)((p->ray.wall_hit.y - pixel) / SIZE);
	}
	if (p->ray.distance < SIZE * 2 && p->ray.hit_content == 'D')
	{
		game->door_sound_played = 0;
		game->door_open = 1;
		game->data->square_map[map_y][map_x] = 'd';

	}
	else if (p->ray.distance < SIZE * 2 && p->ray.hit_content == 'd')
	{
		game->door_open = 0;
		game->door_sound_played = 0;
		game->data->square_map[map_y][map_x] = 'D';
	}
}

void	control_mouse(t_game *game)
{
	if (game->mouse.show_mouse == 0)
		mlx_mouse_show(game->mlx_ptr, game->mlx_win);
	if (game->mouse.show_mouse == 1)
		mlx_mouse_hide(game->mlx_ptr, game->mlx_win);
	game->mouse.show_mouse = !game->mouse.show_mouse;
}

int	key_press(int keycode, t_game *game)
{
	t_player *p;

	p = &game->data->player;
	if (keycode == ESC)
		shutdown2(game);
	if (keycode == LCTRL)
		control_mouse(game);
	if (keycode == W)
		p->keys.up = 1;
	if (keycode == S)
		p->keys.down = 1;
	if (keycode == A)
		p->keys.left = 1;
	if (keycode == D)
		p->keys.right = 1;
	if (keycode == LEFT)
		p->keys.rot_left = 1;
	if (keycode == RIGHT)
		p->keys.rot_right = 1;
	if (keycode == E)
		open_door(game);
	if (keycode == UP)
		game->screen_center += 10;
	if (keycode == DOWN)
		game->screen_center -= 10; 
	return (0);
}

int	gun_fire(int button, int x, int y, void *param)
{
	t_game *game;

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

void	mouse_movement(t_game *game, int new_x, int new_y)
{
	double	delta_x;
	double 	delta_y;

	delta_x = (new_x - 600) * MOUSE_SENSITIVITY;
	delta_y = (new_y - 350);
	game->data->player.angle += delta_x;
	game->screen_center -= delta_y;
	if (game->screen_center >= HEIGHT)
		game->screen_center = HEIGHT;
	if (game->screen_center <= 0)
		game->screen_center = 0;
	mlx_mouse_move(game->mlx_ptr, game->mlx_win, 600, 350);
}

int	mouse_move(int x, int y, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		if (game->mouse.show_mouse == false)
			mouse_movement(game, x, y);
	}
	return (0);
}

void	capture_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, 2, (1L << 0), key_press, game);
	mlx_hook(game->mlx_win, 3, (1L << 1), key_release, game);
	mlx_hook(game->mlx_win, 17, (1L << 17), &shutdown2, game);
	mlx_hook(game->mlx_win, 6, (1L << 6), mouse_move, game);
	mlx_mouse_hook(game->mlx_win, gun_fire, game);
}
