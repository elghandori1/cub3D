NAME = cub3D
LIBFT = libft/libft.a

SRC = main.c get_next_line.c \
	  $(addprefix ./check_map/, check_map.c fill_content_map.c check_content.c check_texture.c \
	  	get_textures.c helpers.c get_color.c get_map.c check_player.c check_identifiers.c) \
	  $(addprefix ./Rendering/, render_map.c rendering.c utils.c check_walls.c) \
	  $(addprefix ./hooks/, moves.c)

OBJ = $(SRC:.c=.o)

CC = cc

# CFLAGS = -Wall -Wextra -Werror
%.o : %.c libft/libft.h cub3D.h
	$(CC) $(CFLAGS) -I/usr/include -Imlx -O3 -c $< -o $@

all : $(NAME)

$(LIBFT):
	make -C libft

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -rf $(OBJ)
	make clean -C libft

fclean:
	rm -rf $(NAME) $(OBJ)
	make fclean -C libft

clear:
	clear

re: fclean all clean clear

