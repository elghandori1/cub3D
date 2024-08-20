#include "../cub3D.h"

void	get_player(t_game *cub3d, int i, int j, int *found)
{
    if ((*found)++)
		ft_error(cub3d,"one player must exist in the map !\n");
	cub3d->map->player.x = j * SIZE + SIZE / 2;
	cub3d->map->player.y = i * SIZE + SIZE / 2;
	if (cub3d->map->map[i][j] == 'N')
		cub3d->map->player.angle = 270;
	else if (cub3d->map->map[i][j] == 'S')
		cub3d->map->player.angle = 90;
	else if (cub3d->map->map[i][j] == 'E')
		cub3d->map->player.angle = 180;
	else
		cub3d->map->player.angle = 0;

}
void check_player(t_game *cub3d)
{
    int i = 0;
    int j = 0;
    int found = 0;

    while (cub3d->map->map[i])
    {
        while (cub3d->map->map[i][j])
        {
            if (ft_search(cub3d->map->map[i][j], "ENSW"))
                get_player(cub3d, i, j, &found);
            else if (!ft_search(cub3d->map->map[i][j], "10 \n"))
                ft_error(cub3d, "Error: Invalid character in the map!\n");
            j++;
        }
        j = 0;
        i++;
    }
}
