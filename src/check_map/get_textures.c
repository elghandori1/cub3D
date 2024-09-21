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
			tmp = ft_substr(content[i - 1] + ft_strlen(target), 0,
					ft_strlen(content[i - 1] + ft_strlen(target)) - 1);
			ret = ft_strtrim(tmp, " \t");
			return (ret);
		}
	}
	return (NULL);
}

void	get_textures(t_game *cub3d)
{
	cub3d->data->ea_texture = get_from_file(cub3d->data->content, "EA");
	cub3d->data->no_texture = get_from_file(cub3d->data->content, "NO");
	cub3d->data->so_texture = get_from_file(cub3d->data->content, "SO");
	cub3d->data->we_texture = get_from_file(cub3d->data->content, "WE");
	if (open(cub3d->data->ea_texture, O_RDONLY) < 0
		|| open(cub3d->data->so_texture, O_RDONLY) < 0
		|| open(cub3d->data->we_texture, O_RDONLY) < 0
		|| open(cub3d->data->no_texture, O_RDONLY) < 0)
		ft_error(cub3d, "couldn't open texture !\n");
}
