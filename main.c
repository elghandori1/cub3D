#include "cub3D.h"

int main(int ac, char **av)
{
    t_cub3d *cub3d = NULL;

    if (ac != 2)
        ft_error(cub3d, "Error: Usage: ./cub3d <map_file.cub>\n");
    check_map(&cub3d, av[1]);
    
    free_cub3d(cub3d);
    return 0;
}
