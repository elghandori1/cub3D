#include "../cub3D.h"

void	get_player(t_cub3d *cub3d, int i, int j, int *found)
{
    if ((*found)++)
		ft_error("one player must exist in the map !\n");
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
void	check_player(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	found;

	found = 0;;
	i = -1;
	j = 0;
    while (cub3d->map->map[++i])
	{
        while (cub3d->map->map[i][j])
		{
            if(ft_search(cub3d->map->map[i][j],"ENSW"))
                get_player(cub3d, i, j, &found);
            else if (!ft_search(cub3d->map->map[i][j], "1 0\n"))
				ft_error("bad charachter in the map !\n");
            j++;
        }
        j=0;
    }
}
