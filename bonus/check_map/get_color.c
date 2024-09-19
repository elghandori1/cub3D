#include "../cub3d_bonus.h"

int	check_colors_format(char **tab, t_game *cub3d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!tab || !tab[0])
		ft_error(cub3d, "you need to put some colors :)\n");
	while (tab[i])
	{
		while (tab[i][j])
		{
			if (!ft_isdigit(tab[i][j]))
				ft_error(cub3d, "colors must be numbers!\n");
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	get_rgb(int color, t_game *cub3d)
{
	if (color >= 0 && color <= 255)
		return (color);
	else
		ft_error(cub3d, "colors must be included in [0,255]\n");
	return (0);
}

void	get_colors(t_game *cub3d)
{
	char	**floor;
	char	**ciel;

	cub3d->data->c_color = get_from_file(cub3d->data->content, "C");
	cub3d->data->f_color = get_from_file(cub3d->data->content, "F");
	ciel = ft_split(cub3d->data->c_color, ',');
	floor = ft_split(cub3d->data->f_color, ',');
	if (check_colors_format(ciel, cub3d) != 3
		|| check_colors_format(floor, cub3d) != 3)
		ft_error(cub3d, " colors must be in this form : R,G,B\n");
	cub3d->data->floor_color.r = get_rgb(ft_atoi(floor[0]), cub3d);
	cub3d->data->floor_color.g = get_rgb(ft_atoi(floor[1]), cub3d);
	cub3d->data->floor_color.b = get_rgb(ft_atoi(floor[2]), cub3d);
	cub3d->data->ciel_color.r = get_rgb(ft_atoi(ciel[0]), cub3d);
	cub3d->data->ciel_color.g = get_rgb(ft_atoi(ciel[1]), cub3d);
	cub3d->data->ciel_color.b = get_rgb(ft_atoi(ciel[2]), cub3d);
	ft_free(ciel);
	ft_free(floor);
}

