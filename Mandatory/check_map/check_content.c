#include "../cub3D.h"

void	check_content(t_game *cub3d)
{
	check_identifier(cub3d);
	check_textures_path(cub3d->data->content, cub3d);
	get_textures(cub3d);
	get_colors(cub3d);
	get_data(cub3d);
	get_square_map(cub3d);
	check_player(cub3d);
	if (!check_walls(cub3d))
		ft_error(cub3d, "Error: Map is not surrounded by walls !\n");
}
