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

	if (map->map && map->square_map)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->map[i]);
			free(map->square_map[i]);
			i++;
		}
		free(map->map);
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

void	shutdown(t_game *game)
{
	if (!game)
		return ;
	if (game->textures[0])
	{
		mlx_destroy_image(game->mlx_ptr, game->textures[0]->img);
		mlx_destroy_image(game->mlx_ptr, game->textures[1]->img);
		mlx_destroy_image(game->mlx_ptr, game->textures[2]->img);
		mlx_destroy_image(game->mlx_ptr, game->textures[3]->img);
		mlx_destroy_image(game->mlx_ptr, game->frame_buffer.img);
		free(game->textures[0]);
		free(game->textures[1]);
		free(game->textures[2]);
		free(game->textures[3]);
	}
	if (game->data)
	{
		free_map(game->data);
		free(game->data);
	}
	if (game->mlx_win)
		mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	// if (game->mlx_ptr)
	// {
	// 	mlx_destroy_display(game->mlx_ptr);
	// 	free(game->mlx_ptr);
	// }
}
