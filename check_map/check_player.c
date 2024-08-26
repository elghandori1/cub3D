#include "../cub3D.h"

void	get_player(t_game *cub3d, int i, int j, int *found)
{
    double rad;

    if ((*found)++)
		ft_error(cub3d,"one player must exist in the map !\n");
	cub3d->map->player.x = (float)j;
	cub3d->map->player.y = (float)i;
if (cub3d->map->map[i][j] == 'N')
        cub3d->map->player.angle = PI / 2;
    else if (cub3d->map->map[i][j] == 'S')
        cub3d->map->player.angle = 3 * PI / 2;
    else if (cub3d->map->map[i][j] == 'E')
        cub3d->map->player.angle = 0;
    else // 'W'
        cub3d->map->player.angle = PI;
    cub3d->map->player.dir_x = cos(cub3d->map->player.angle);
    cub3d->map->player.dir_y = -sin(cub3d->map->player.angle);
}

void check_player(t_cub3d *cub3d)
{
    int i = 0;
    int j = 0;
    int found = 0;
    int bad_char = 0;

    while (cub3d->map->map[i])
    {
        while (cub3d->map->map[i][j])
        {
            if (ft_search(cub3d->map->map[i][j], "ENSW"))
                get_player(cub3d, i, j, &found);
            else if (!ft_search(cub3d->map->map[i][j], "1 0\n"))
                bad_char++;
        j++;
        }
        j = 0;
        i++;
    }
   	if (found != 1)
		ft_error(cub3d,"one player must exist in the map \n");
	if (bad_char)
		ft_error(cub3d,"bad charachter in the map !\n");
}
