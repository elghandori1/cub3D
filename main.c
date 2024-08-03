#include "cub3D.h"

int main(int ac,char **av)
{
    t_cub3d *cub3d;

    if (ac != 2)
        ft_error("Error: Usage: ./cub3d <map_file.cub>\n");
    check_map(&cub3d,av[1]);
}