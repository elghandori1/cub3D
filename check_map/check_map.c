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

    (*cub3d)->map = malloc(sizeof(t_map));
    if (!(*cub3d)->map)
    {
        free(*cub3d);
        ft_error(NULL, "Memory allocation failed for map!");
    }

    ft_memset((*cub3d)->map, 0, sizeof(t_map));
    fill_content_map(file, *cub3d);
    check_content(*cub3d);
}
