#include "../cub3D.h"

int rows_nbr(int fd)
{
    int len;
    char *line;

    len = 0;
    line = get_next_line(fd);
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        len++;
    }
    free(line);
    return (len);
    
}

void	fill_content_data(char *map_file, t_game *cub3d)
{
    int fd;
    int i;

    i = 0;
    fd = open(map_file, O_RDONLY);
    if (fd == -1)
        perror("Error opening file"), exit(EXIT_FAILURE);
    cub3d->data->rows = rows_nbr(fd);
    close(fd);
    fd = open(map_file, O_RDONLY);
    if (fd == -1)
        perror("Error opening file"), exit(EXIT_FAILURE);
    cub3d->data->content = malloc(sizeof(char *) * (cub3d->data->rows +1));
   	cub3d->data->content[i] = get_next_line(fd);
	while (i < cub3d->data->rows && cub3d->data->content[i++])
		cub3d->data->content[i] = get_next_line(fd);
    close(fd);
}
