#include "../cub3D.h"

int	line_counter(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void check_texture_file(char *path)
{
    const char *ext = ".xpm";
    while (path && *path == ' ')
        path++;
    int len = line_counter(path) - 4;
    if (len < 0 || ft_strncmp(path + len, ext, 4) != 0)
        ft_error("Error: Texture file must have .xpm extension\n");
}

void check_textures(char **content)
{
    int i = 0;
    char *path;

    while (content[i])
    {
        if (ft_strncmp(content[i], "WE", 2) == 0 || ft_strncmp(content[i], "SO", 2) == 0 ||
            ft_strncmp(content[i], "NO", 2) == 0 || ft_strncmp(content[i], "EA", 2) == 0)
        {
            path = ft_strchr(content[i], ' ');
            if (path != NULL)
                check_texture_file(path);
            else
                ft_error("Error: Missing texture file path\n");
        }
        i++;
    }
}