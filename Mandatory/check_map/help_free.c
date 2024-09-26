#include "../cub3D.h"

void	free_textures(t_data *map)
{
	if (map->so_texture)
		free(map->so_texture);
	if (map->no_texture)
		free(map->no_texture);
	if (map->ea_texture)
		free(map->ea_texture);
	if (map->we_texture)
		free(map->we_texture);
}

void	free_colors(t_data *map)
{
	if (map->c_color)
		free(map->c_color);
	if (map->f_color)
		free(map->f_color);
}

void	free_map_content(t_data *map)
{
	 int	i;

	if (map->map)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	if (map->square_map)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->square_map[i]);
			i++;
		}
		free(map->square_map);
	}
}

void	free_map(t_data *map)
{
	int	i;

	if (!map)
		return ;
	if (map->content)
	{
		i = 0;
		while (map->content[i])
			free(map->content[i++]);
		free(map->content);
	}
	free_textures(map);
	free_colors(map);
	free_map_content(map);
}

void	free_textures_res(t_game *game)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (game->textures[i])
			mlx_destroy_image(game->mlx_ptr, game->textures[i]->img);
	}
	if (game->frame_buffer.img)
		mlx_destroy_image(game->mlx_ptr, game->frame_buffer.img);
}


int	turnoff(t_game *game)
{
	if (!game)
		return (exit(0), 0);
	free_textures_res(game);
	m_alloc(0, FREE);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	return (exit(0), 0);
}
