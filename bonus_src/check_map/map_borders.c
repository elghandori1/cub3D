#include "../cub3d_bonus.h"

void	check_map_height(t_game *cub3d)
{
	int	len;

	len = cub3d->data->height - 1;
	if (len == 0)
	{
		ft_error(cub3d, "Error: Map borders are invalid!\n");
	}
}

void	check_top_border(t_game *cub3d)
{
	int	idx;

	idx = 0;
	if (!check_row(cub3d->data->map[0]))
	{
		ft_error(cub3d, "Error: Map borders are invalid!\n");
	}
	while (cub3d->data->map[0][idx])
	{
		if (ft_search(cub3d->data->map[0][idx], "ENSW"))
		{
			ft_error(cub3d, "Error: Map borders are invalid!\n");
		}
		idx++;
	}
}


void	check_bottom_border(t_game *cub3d)
{
	int (len), (idx);
	len = cub3d->data->height - 1;
	idx = 0;
	if (!check_row(cub3d->data->map[len]))
	{
		ft_error(cub3d, "Error: Map borders are invalid!\n");
	}
	while (cub3d->data->map[len][idx])
	{
		if (ft_search(cub3d->data->map[len][idx], "ENSW"))
		{
			ft_error(cub3d, "Error: Map borders are invalid!\n");
		}
		idx++;
	}
}

void	check_top_bottom_borders(t_game *cub3d)
{
	check_top_border(cub3d);
	check_bottom_border(cub3d);
}

void	check_left_right_borders(t_game *cub3d)
{
	int	len;

	int (i), (start), (end);
	len = cub3d->data->height - 1;
	i = 1;
	while (i < len)
	{
		start = 0;
		end = ft_strlen(cub3d->data->map[i]) - 2;
		while (cub3d->data->map[i][start] == ' ')
			start++;
		while (end > start && cub3d->data->map[i][end] == ' ')
			end--;
		if (cub3d->data->map[i][start] != '1'
			|| cub3d->data->map[i][end] != '1')
		{
			ft_error(cub3d, "Error: Map borders are invalid!\n");
		}
		i++;
	}
}

void	map_borders(t_game *cub3d)
{
	check_map_height(cub3d);
	check_top_bottom_borders(cub3d);
	check_left_right_borders(cub3d);
}