#include "../cub3D.h"

char	*get_from_file(char **content, char *target)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = 0;
	while (content[i])
	{
		if (!ft_strncmp(content[i++], target, ft_strlen(target)))
		{
			tmp = ft_substr(content[i - 1] + ft_strlen(target), 0, \
				ft_strlen(content[i - 1] + ft_strlen(target)) - 1);
			ret = ft_strtrim(tmp, " \t");
			free(tmp);
			return (ret);
		}
	}
	return (NULL);
}

// void get_textures(t_cub3d *cub3d)
// {
//     cub3d->map->ea_texture = get_from_file(cub3d->map->content, "EA");
// 	cub3d->map->no_texture = get_from_file(cub3d->map->content, "NO");
// 	cub3d->map->so_texture = get_from_file(cub3d->map->content, "SO");
// 	cub3d->map->we_texture = get_from_file(cub3d->map->content, "WE");
//     if (open(cub3d->map->ea_texture, O_RDONLY) < 0
// 		|| open(cub3d->map->so_texture, O_RDONLY) < 0
// 		|| open(cub3d->map->we_texture, O_RDONLY) < 0
// 		||open(cub3d->map->no_texture, O_RDONLY) < 0)
// 		ft_error("couldn't open texture !\n");
// }

