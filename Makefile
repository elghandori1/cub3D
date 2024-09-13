NAME = cub3D
NAME_BONUS = cub3D_bonus
LIBFT = libft/libft.a

SRC = main.c get_next_line.c \
	  $(addprefix ./check_map/, check_map.c  check_content.c check_texture.c \
	  	get_textures.c helpers.c get_color.c get_map.c check_player.c check_identifiers.c check_walls.c fill_content_map.c)  \
	  $(addprefix ./Rendering/, render_map.c  rendering.c  utils.c raycasting.c)\
	  $(addprefix ./hooks/, moves.c)

SRC_BONUS = main_bonus.c get_next_line.c \
	  $(addprefix ./check_map/, check_map.c  check_content.c check_texture.c \
	  	get_textures.c helpers.c get_color.c get_map.c check_player.c check_identifiers.c check_walls.c fill_content_map.c)  \
	  $(addprefix ./Rendering/, render_map.c utils.c raycasting.c)\
	  $(addprefix ./hooks/, moves.c move_mouse.c)

OBJ = $(SRC:.c=.o)
OBJSB = $(SRC_BONUS:.c=.o) 

CC = cc
CFLAGS = -g3 #-Wall -Wextra -Werror

%.o : %.c libft/libft.h cub3D.h
	$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@

all : $(NAME)

$(LIBFT):
	make -C libft

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

$(NAME_BONUS) : $(OBJSB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJSB) $(LIBFT) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	rm -rf $(OBJ) $(OBJSB)
	make clean -C libft

fclean:
	rm -rf $(NAME) $(NAME_BONUS) $(OBJ) $(OBJSB)
	make fclean -C libft

re: fclean all
