#include "../cub3D.h"

void valid_content(t_game *cub3d)
{
    int i;
 int j;

 i = -1;
 j = 0;
 while (cub3d->data->content[++i])
 {
  if (ft_search(cub3d->data->content[i][0], " 10FC\n"))
   continue ;
  else if (ft_strncmp(cub3d->data->content[i], "WE", 2)
   && ft_strncmp(cub3d->data->content[i], "NO", 2)
   && ft_strncmp(cub3d->data->content[i], "EA", 2)
   && ft_strncmp(cub3d->data->content[i], "SO", 2))
   ft_error(cub3d, "Error: bad character in content of file\n");
 }
}

int check_map_last(t_game *cub3d)
{
    int x = 0;

    while (cub3d->data->content[x])
    {
        if (ft_search(cub3d->data->content[x][0], " 01"))
            break;
        x++;
    }
    int len = map_len(cub3d->data->content) + 1;
    cub3d->data->last_map = m_alloc(len * sizeof(char *),ALLOC);
    int a = 0;
    while (cub3d->data->content[x])
    {
        cub3d->data->last_map[a] = ft_strdup(cub3d->data->content[x]);
        a++;
        x++;
    }
    cub3d->data->last_map[a] = NULL;
    int i = 0;
    while (cub3d->data->last_map[i])
    {
        if (ft_strncmp(cub3d->data->last_map[i], "WE", 2) == 0 || ft_strncmp(cub3d->data->last_map[i], "NO", 2) == 0 ||
            ft_strncmp(cub3d->data->last_map[i], "EA", 2) == 0 || ft_strncmp(cub3d->data->last_map[i], "SO", 2) == 0 ||
            ft_strncmp(cub3d->data->last_map[i], "C", 1) == 0 || ft_strncmp(cub3d->data->last_map[i], "F", 1) == 0)
			return 1;
        i++;
    }
    return 0;
}

void check_content(t_game *cub3d)
{ 
	if (!check_map_last(cub3d))
    {
    valid_content(cub3d);
    check_identifier(cub3d);
    check_textures_path(cub3d->data->content, cub3d);
    get_textures(cub3d);
    get_colors(cub3d);
    get_map(cub3d);
    get_square_map(cub3d);
    check_player(cub3d);
     if (!check_walls(cub3d))
        ft_error(cub3d, "Error: Map borders are invalid! 55\n");
    }else
		ft_error(cub3d,"Error: The map must be the last!\n");
}
