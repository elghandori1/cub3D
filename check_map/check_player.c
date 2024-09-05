#include "../cub3D.h"

void	get_player(t_game *cub3d, int i, int j, int *found)
{
    if ((*found)++)
		ft_error(cub3d,"one player must exist in the map !\n");
	cub3d->data->player.x = j * SIZE + SIZE / 2;
	cub3d->data->player.y = i * SIZE + SIZE / 2;
    if (cub3d->data->map[i][j] == 'N')
        cub3d->data->player.angle = 3 * PI / 2;
    else if (cub3d->data->map[i][j] == 'S')
        cub3d->data->player.angle = PI / 2;
    else if (cub3d->data->map[i][j] == 'E')
        cub3d->data->player.angle = 0;
    else if (cub3d->data->map[i][j] == 'W')
        cub3d->data->player.angle = PI;
    cub3d->data->player.dir_x = cos(cub3d->data->player.angle);
    cub3d->data->player.dir_y = sin(cub3d->data->player.angle);
}

void check_player(t_game *cub3d)
{
    int i = 0;
    int j = 0;
    int found = 0;
    int bad_char = 0;

    while (cub3d->data->map[i])
    {
        while (cub3d->data->map[i][j])
        {
            if (ft_search(cub3d->data->map[i][j], "ENSW"))
                get_player(cub3d, i, j, &found);
            else if (!ft_search(cub3d->data->map[i][j], "1 0\n"))
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
