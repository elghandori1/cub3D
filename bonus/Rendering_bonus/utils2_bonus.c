#include "../cub3d_bonus.h"


t_image *load_texture(t_game *game, char *path)
{
	t_image	*img;
	int		n;

	img = malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->width, &img->height);
	if (!img->img)
		ft_error(game, "Texture loading failed\n");
	img->addr = mlx_get_data_addr(img->img, &n, &n, &n);
    if (!img->addr)
        return (NULL);
	return (img);
}

void    free_textures(t_image **textures)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if (textures[i])
        {
            if (textures[i]->img)
                free(textures[i]->img);
            if (textures[i]->addr)
                free(textures[i]->addr);
            free(textures[i]);
        }
        i++;
    }
}

void	initialize_textures(t_game *game)
{
    int i;

	game->textures[NORTH] = load_texture(game, game->data->no_texture);
	game->textures[SOUTH] = load_texture(game, game->data->so_texture);
	game->textures[WEST] = load_texture(game, game->data->we_texture);
	game->textures[EAST] = load_texture(game, game->data->ea_texture);
    game->textures[SHOOT_BOARD] = load_texture(game, "./textures/shot-board.xpm");
    game->textures[DOOR] = load_texture(game, "./textures/door.xpm");
    i = 0;
    while (i < 6)
    {
        if (!game->textures[i])
            free_textures(game->textures);
        i++;
    }
    game->gun[0] = load_texture(game, "./textures/pis-0.xpm");
    game->gun[1] = load_texture(game, "./textures/pis-1.xpm");
    game->gun[2] = load_texture(game, "./textures/pis-2.xpm");
    game->gun[3] = load_texture(game, "./textures/pis-3.xpm");
}

void	initialize_frame(t_game *g)
{
	g->frame_buffer.img = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	if (!g->frame_buffer.img)
		ft_error(g ,"Frame buffer creation failed\n");
	g->frame_buffer.addr = mlx_get_data_addr(g->frame_buffer.img,
											&g->frame_buffer.bits_per_pixel,
											&g->frame_buffer.line_length,
											&g->frame_buffer.endian);
    if (!g->frame_buffer.addr)
        return (ft_error(g, "Failed to get data addr\n"));
}

