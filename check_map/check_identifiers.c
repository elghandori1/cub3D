#include "../cub3D.h"

void initialize_identifiers(t_map *map)
{
    map->we = 0;
    map->so = 0;
    map->no = 0;
    map->ea = 0;
    map->c = 0;
    map->f = 0;
}

void check_texture_identifiers(t_map *map, char *line)
{
    if (ft_strncmp(line, "WE", 2) == 0)
    {
        if (map->we) ft_error("error: duplicate WE identifier\n");
        map->we = 1;
    }
    else if (ft_strncmp(line, "SO", 2) == 0)
    {
        if (map->so) ft_error("error: duplicate SO identifier\n");
        map->so = 1;
    }
    else if (ft_strncmp(line, "NO", 2) == 0)
    {
        if (map->no) ft_error("error: duplicate NO identifier\n");
        map->no = 1;
    }
    else if (ft_strncmp(line, "EA", 2) == 0)
    {
        if (map->ea) ft_error("error: duplicate EA identifier\n");
        map->ea = 1;
    }
}

void check_color_identifiers(t_map *map, char *line)
{
    if (ft_strncmp(line, "C", 1) == 0)
    {
        if (map->c) ft_error("error: duplicate C color\n");
        map->c = 1;
    }
    else if (ft_strncmp(line, "F", 1) == 0)
    {
        if (map->f) ft_error("error: duplicate F color\n");
        map->f = 1;
    }
}

void validate_identifiers(t_map *map)
{
    if (!map->we || !map->so || !map->no || !map->ea)
        ft_error("error: problem in identifier\n");
    if (!map->c || !map->f)
        ft_error("error: problem in color\n");
}


void check_identifier(t_cub3d *content)
{
    initialize_identifiers(content->map);
    int i;

    i = 0;
    while (content->map->content[i])
    {
        if (ft_strcmp(content->map->content[i], "\n") == 0 \
            || ft_strncmp(content->map->content[i], "1", 1) == 0 \
            || ft_strncmp(content->map->content[i], "0", 1) == 0)
        {
            i++;
            continue;
        }
        check_texture_identifiers(content->map, content->map->content[i]);
        check_color_identifiers(content->map, content->map->content[i]);
        i++;
    }
    validate_identifiers(content->map);
}
