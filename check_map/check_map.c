#include "../cub3D.h"

int	has_cub_extension(const char *f_name)
{
    const char *ext = ".cub";

	int len;
	len = ft_strlen(f_name) - 4;
	return (ft_strncmp(f_name + len,ext ,4) == 0);
}

int check_empty(char *f_name)
{
    int fd;
	int rslt;
	char buf;

    fd = open(f_name, O_RDONLY);
    if (fd == -1)
	{
        perror("open");
        exit(EXIT_FAILURE);
    }
    rslt = read(fd, &buf, 1);
    close(fd);
    return rslt;
}
t_map   *initialize_map(void)
{
    t_map *map = malloc(sizeof(t_map));
    if (!map)
        return NULL;

    map->we = 0;
    map->so = 0;
    map->no = 0;
    map->ea = 0;
    map->f = 0;
    map->c = 0;
    map->content = NULL;
    map->so_texture = NULL;
    map->no_texture = NULL;
    map->ea_texture = NULL;
    map->we_texture = NULL;
    map->c_color = NULL;
    map->f_color = NULL;
    map->floor_color = NULL;
    map->ciel_color = NULL;
    map->map = NULL;
    map->len = 0;
    map->max_len = 0;

    return map;
}


void check_map(t_game **cub3d, char *file)
{
    if (open(file, __O_DIRECTORY) != -1)
        ft_error(*cub3d, "this is a directory!");

    if (!has_cub_extension(file))
        ft_error(*cub3d, "bad extension!");

    if (!check_empty(file))
        ft_error(*cub3d, "empty file!");

    *cub3d = malloc(sizeof(t_game));
    if (!*cub3d)
        ft_error(NULL, "Memory allocation failed for cub3d!");

    (*cub3d)->map = initialize_map();
    if (!(*cub3d)->map)
    {
        free(*cub3d);
        ft_error(NULL, "Memory allocation failed for map!");
    }
    fill_content_map(file, *cub3d);
    check_content(*cub3d);
}
