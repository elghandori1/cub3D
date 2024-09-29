NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast
LIBFT = include/libft/libft.a
CUTE_SOUND = include/cute_sound/cute_sound.o
MLXFLAGS = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
SDL = -I/usr/include/SDL2/

SRC = 	helpers/get_next_line.c helpers/gc.c \
		$(addprefix ./mandatory_src/, main.c raycasting.c utils.c utils2.c render_wall.c moves.c move_player.c) \
		$(addprefix ./mandatory_src/check_map/, check_map.c check_content.c check_texture.c \
	  				get_textures.c helpers.c get_color.c get_map.c check_player.c \
					check_identifiers.c check_walls.c fill_content_map.c help_free.c \
					get_square_map.c map_borders.c check_map_last.c)  \

SRC_BONUS = helpers/get_next_line.c helpers/gc.c\
	  $(addprefix ./bonus_src/, main_bonus.c minimap_bonus.c utils_bonus.c utils2_bonus.c \
	  							moves_bonus.c render_bonus.c raycasting_bonus.c \
								hooks_bonus.c init_bonus.c mouse_bonus.c raycasting_bonus2.c) \
	  $(addprefix ./bonus_src/check_map/, check_map.c  check_content.c check_texture.c \
	  									get_textures.c helpers.c get_color.c get_map.c \
										check_player.c check_identifiers.c check_walls.c \
										fill_content_map.c get_square_map.c map_borders.c check_map_last.c)

OBJ = $(SRC:.c=.o)
OBJSB = $(SRC_BONUS:.c=.o) 

%.o : %.c
	$(CC) $(CFLAGS)  -I/usr/include -Imlx -c $< -o $@

all : $(NAME)

$(LIBFT):
	make -C include/libft
$(CUTE_SOUND) :
	make -C include/cute_sound

$(NAME) : $(OBJ) $(LIBFT)  include/libft/libft.h ./mandatory_src/cub3D.h
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(NAME_BONUS) : $(OBJSB) $(LIBFT) $(CUTE_SOUND) include/libft/libft.h ./bonus_src/cub3d_bonus.h
	$(CC) $(CFLAGS) $(SDL) $(OBJSB) $(LIBFT) $(CUTE_SOUND) $(MLXFLAGS) -o $(NAME_BONUS) -lSDL2

bonus: $(NAME_BONUS)

clean:
	rm -rf $(OBJ) $(OBJSB)
	make clean -C include/libft
	make clean -C include/cute_sound


fclean:
	rm -rf $(NAME) $(NAME_BONUS) $(OBJ) $(OBJSB)
	make fclean -C include/libft
	make fclean -C include/cute_sound

re: fclean all

rebonus: fclean bonus

.SECONDARY: $(OBJ) $(OBJSB)