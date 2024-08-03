#include "../cub3D.h"

void check_identifier(char **content)
{
    int i = 0;
    int we = 0, so = 0, no = 0, ea = 0, c = 0, f = 0;

    while (content[i])
    {
        if (ft_strncmp(content[i], "WE", 2) == 0)
            we++;
        else if (ft_strncmp(content[i], "SO", 2) == 0)
            so++;
        else if (ft_strncmp(content[i], "NO", 2) == 0)
            no++;
        else if (ft_strncmp(content[i], "EA", 2) == 0)
            ea++;
        else if (ft_strncmp(content[i], "C", 1) == 0)
            c++;
        else if (ft_strncmp(content[i], "F", 1) == 0)
            f++;
        else if (ft_strncmp(content[i], "1", 1) == 0 || ft_strncmp(content[i], "0", 1) == 0)
            break;
        else if (ft_strcmp(content[i], "\n") == 0)
        {
            i++;
            continue;
        }
        else
            ft_error("Error: Problem in identifier\n");
        i++;
    }
    if (we != 1 || so != 1 || no != 1 || ea != 1)
        ft_error("Error: Duplicate textures in the file!\n");
    if (c != 1 || f != 1)
        ft_error("Error: Problem in color\n");
}

int check_map_last(char **check_last)
{
    int i = 0;
    while (check_last[i])
    {
        if (ft_strncmp(check_last[i], "WE", 2) == 0 || ft_strncmp(check_last[i], "NO", 2) == 0 \
            || ft_strncmp(check_last[i], "EA", 2) == 0 || ft_strncmp(check_last[i], "SO", 2) == 0 \
            || ft_strncmp(check_last[i], "C", 1) == 0 || ft_strncmp(check_last[i], "F", 1) == 0)
            break;
        if (ft_strncmp(check_last[i], "1", 1) == 0 || ft_strncmp(check_last[i], "0", 1) == 0)
            return 1;
        i++;
    }
    return 0;
}

void	check_content(t_cub3d *cub3d)
{
	if(check_map_last(cub3d->map->content))
		ft_error("the map must be the last !\n");
	else
	{
    	check_identifier(cub3d->map->content);
    	check_textures(cub3d->map->content);
	}

}
