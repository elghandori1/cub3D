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
	// if (map->floor_color)
	// 	free(map->floor_color);
	// if (map->ciel_color)
	// 	free(map->ciel_color);
}

void	free_map_content(t_data *map)
{
	size_t	i;

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

void	free_cub3d(t_game *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->mlx_ptr)
		mlx_destroy_display(cub3d->mlx_ptr);
	if (cub3d->data)
	{
		free_map(cub3d->data);
		free(cub3d->data);
	}
}
