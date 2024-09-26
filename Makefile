NAME = cub3D
NAME_BONUS = cub3D_bonus
LIBFT = include/libft/libft.a
CUTE_SOUND = include/cute_sound/cute_sound.o

SRC = ./Mandatory/main.c ./helpers/get_next_line.c ./helpers/gc.c\
	  $(addprefix ./Mandatory/check_map/, check_map.c  check_content.c check_texture.c \
	  	get_textures.c helpers.c get_color.c get_map.c check_player.c check_identifiers.c check_walls.c  \
		fill_content_map.c help_free.c  get_square_map.c map_borders.c)  \
	  $(addprefix ./Mandatory/Rendering/, raycasting.c utils.c utils2.c render_wall.c)\
	  $(addprefix ./Mandatory/hooks/, moves.c move_player.c) \

SRC_BONUS = ./bonus_src/main_bonus.c ./helpers/get_next_line.c ./helpers/gc.c\
	  $(addprefix ./bonus_src/check_map/, check_map.c  check_content.c check_texture.c \
	  	get_textures.c helpers.c get_color.c get_map.c check_player.c check_identifiers.c check_walls.c fill_content_map.c )  \
	  $(addprefix ./bonus_src/minimap_bonus/, minimap_bonus.c)\
	  $(addprefix ./bonus_src/Rendering_bonus/, utils_bonus.c utils2_bonus.c render_bonus.c raycasting_bonus.c)\
	  $(addprefix ./bonus_src/hooks_bonus/, moves_bonus.c) \

OBJ = $(SRC:.c=.o)
OBJSB = $(SRC_BONUS:.c=.o) 

CC = cc
CFLAGS = -g3 -fsanitize=address #-Ofast #-Wall -Wextra -Werror 
SDL = -I/usr/include/SDL2/ -I/usr/include

%.o : %.c include/libft/libft.h cub3D.h cub3D_bonus.h
	$(CC) $(CFLAGS) $(SDL) -I/usr/include -Imlx -c $< -o $@

all : $(NAME)

$(LIBFT):
	make -C include/libft

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

$(NAME_BONUS) : $(OBJSB) $(LIBFT)
	$(CC) $(CFLAGS) $(SDL) $(OBJSB) $(LIBFT) $(CUTE_SOUND) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME_BONUS) -lSDL2

bonus: $(NAME_BONUS)

clean:
	rm -rf $(OBJ) $(OBJSB)
	make clean -C include/libft

fclean:
	rm -rf $(NAME) $(NAME_BONUS) $(OBJ) $(OBJSB)
	make fclean -C include/libft

re: fclean all

rebonus: fclean bonus
