#include "../cub3D.h"

void check_identifier(char **content)
{
    int	i;
	i = -1;
	while (content[++i])
	{
		if (!ft_strcmp(&content[i][0],"\n"))
			continue ;
		else if (ft_strncmp(content[i], "WE", 2)
			&& ft_strncmp(content[i], "NO", 2)
			&& ft_strncmp(content[i], "EA", 2)
			&& ft_strncmp(content[i], "SO", 2))
			ft_error("error:probelm in identifier\n");
	}
}

int line_counter(char *str)
{
    int i = 0;
    while(str[i] && str[i] != '\n')
        i++;
    return i;
}

void check_texture_file(char *path)
{
    const char *ext;
    int len, fd;

    ext = ".xpm";
    fd = 0;
    while(path && *path == ' ')
        path++;
    len = line_counter(path)-4;
    if(!(ft_strncmp(path + len, ext, 4) == 0))
        ft_error("Error: Texture file must have .xpm extension\n");
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Error opening texture file");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void check_textures(char **content)
{
    int i;

    i = 0;
    char *path;
    int no_flag = 0, so_flag = 0, we_flag = 0, ea_flag = 0;
    while(content[i])
    {
        if (ft_strncmp(content[i], "NO", 2) == 0) {
            if (no_flag)
                ft_error("Error: Duplicate NO texture\n");
            no_flag = 1;
        }else if (ft_strncmp(content[i], "SO", 2) == 0) {
            if (so_flag)
                ft_error("Error: Duplicate SO texture\n");
            so_flag = 1;
        } else if (ft_strncmp(content[i], "WE", 2) == 0) {
            if (we_flag)
                ft_error("Error: Duplicate WE texture\n");
            we_flag = 1;
        } else if (ft_strncmp(content[i], "EA", 2) == 0) {
            if (ea_flag)
                ft_error("Error: Duplicate EA texture\n");
            ea_flag = 1;
        } 
        if (ft_strcmp(&content[i][0],"\n"))
            path = ft_strchr(content[i],' ');
        if (path == NULL)
            ft_error("Error: Missing path for texture identifier\n");
        check_texture_file(path);
        i++;
    }
}

void	check_content(t_cub3d *cub3d)
{
    check_identifier(cub3d->map->content);
    check_textures(cub3d->map->content);
}