#include "../cub3d_bonus.h"

void	check_content(t_game *cub3d)
{
    check_identifier(cub3d);
    check_textures_path(cub3d->data->content, cub3d);
    get_textures(cub3d);
	get_colors(cub3d);
    get_data(cub3d);
    cub3d->data->width = cub3d->data->max_len;
    check_player(cub3d);
   	get_square_map(cub3d);
    if (!check_walls(cub3d))
		ft_error(cub3d,"Map is not surrounded by walls !\n");
}
