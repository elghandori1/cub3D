#include "../cub3d_bonus.h"

void create_last_map(t_game *cub3d)
{
    int x = 0;
    while (cub3d->data->content[x])
    {
        if (ft_search(cub3d->data->content[x][0], "01"))
            break;
        x++;
    }

    int len = map_len(cub3d->data->content) + 1;
    cub3d->data->last_map = m_alloc(len * sizeof(char *), ALLOC);

    int a = 0;
    while (cub3d->data->content[x])
    {
        cub3d->data->last_map[a] = ft_strdup(cub3d->data->content[x]);
        a++;
        x++;
    }
    cub3d->data->last_map[a] = NULL;
}

int check_identifiers_in_last_map(t_game *cub3d)
{
    int i = 0;
    while (cub3d->data->last_map[i])
    {
        if (ft_strncmp(cub3d->data->last_map[i], "WE", 2) == 0 || 
            ft_strncmp(cub3d->data->last_map[i], "NO", 2) == 0 ||
            ft_strncmp(cub3d->data->last_map[i], "EA", 2) == 0 || 
            ft_strncmp(cub3d->data->last_map[i], "SO", 2) == 0 ||
            ft_strncmp(cub3d->data->last_map[i], "C", 1) == 0 || 
            ft_strncmp(cub3d->data->last_map[i], "F", 1) == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int check_map_last(t_game *cub3d)
{
    create_last_map(cub3d);
    return check_identifiers_in_last_map(cub3d);
}
