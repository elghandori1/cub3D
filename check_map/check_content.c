#include "../cub3D.h"

void check_map_last(char **check_last)
{
    int i = 0;
    while (check_last[i])
    {
        if (ft_strncmp(check_last[i], "WE", 2) == 0 || ft_strncmp(check_last[i], "NO", 2) == 0 \
            || ft_strncmp(check_last[i], "EA", 2) == 0 || ft_strncmp(check_last[i], "SO", 2) == 0 \
            || ft_strncmp(check_last[i], "C", 1) == 0 || ft_strncmp(check_last[i], "F", 1) == 0)
            break;
        if (ft_strncmp(check_last[i], "1", 1) == 0 || ft_strncmp(check_last[i], "0", 1) == 0)
            ft_error("the map must be the last !\n");
        i++;
    }
}

void	check_content(t_cub3d *cub3d)
{
    check_identifier(cub3d);
    check_textures_path(cub3d->map->content);
    get_textures(cub3d);
	get_colors(cub3d);
    get_map(cub3d);
    check_player(cub3d);
    check_map_last(cub3d->map->content);
    printf("valid map!\n");
}
