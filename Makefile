NAME = cub3D
NAME_BONUS = cub3D_bonus
LIBFT = include/libft/libft.a
CUTE_SOUND = include/cute_sound/cute_sound.o

SRC = 	helpers/get_next_line.c helpers/gc.c \
		$(addprefix ./Mandatory/, main.c raycasting.c utils.c utils2.c render_wall.c moves.c move_player.c) \
		$(addprefix ./Mandatory/check_map/, check_map.c check_content.c check_texture.c \
	  				get_textures.c helpers.c get_color.c get_map.c check_player.c \
					check_identifiers.c check_walls.c fill_content_map.c help_free.c \
					get_square_map.c map_borders.c)  \

SRC_BONUS = helpers/get_next_line.c helpers/gc.c\
	  $(addprefix ./bonus_src/, main_bonus.c minimap_bonus.c utils_bonus.c utils2_bonus.c \
	  							moves_bonus.c render_bonus.c raycasting_bonus.c)\
	  $(addprefix ./bonus_src/check_map/, check_map.c  check_content.c check_texture.c \
	  									get_textures.c helpers.c get_color.c get_map.c \
										check_player.c check_identifiers.c check_walls.c \
										fill_content_map.c get_square_map.c map_borders.c)

OBJ = $(SRC:.c=.o)
OBJSB = $(SRC_BONUS:.c=.o) 

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast #-g3 -fsanitize=address 
MLXFLAGS = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
SDL = -I/usr/include/SDL2/ -I/usr/include

%.o : %.c include/libft/libft.h cub3D.h cub3D_bonus.h
	$(CC) $(CFLAGS) $(SDL) -I/usr/include -Imlx -c $< -o $@

all : $(NAME)

$(LIBFT):
	make -C include/libft
$(CUTE_SOUND) :
	make -C include/cute_sound

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(NAME_BONUS) : $(OBJSB) $(LIBFT) $(CUTE_SOUND)
	$(CC) $(CFLAGS) $(SDL) $(OBJSB) $(LIBFT) $(CUTE_SOUND) $(MLXFLAGS) -o $(NAME_BONUS) -lSDL2

bonus: $(NAME_BONUS)

clean:
	rm -rf $(OBJ) $(OBJSB)
	make clean -C include/libft

fclean:
	rm -rf $(NAME) $(NAME_BONUS) $(OBJ) $(OBJSB)
	make fclean -C include/libft

re: fclean all

rebonus: fclean bonus

.SECONDARY: $(OBJ) $(OBJSB)