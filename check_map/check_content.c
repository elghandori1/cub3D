#include "../cub3D.h"

void	check_content(t_game *cub3d)
{
    check_identifier(cub3d);
    check_textures_path(cub3d->map->content, cub3d);
    get_textures(cub3d);
	get_colors(cub3d);
    get_map(cub3d);
    check_player(cub3d);
   
   printf("valid map!\n");
}
