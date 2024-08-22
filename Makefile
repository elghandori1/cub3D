NAME = cub3D
LIBFT = libft/libft.a

SRC = main.c ./check_map/check_map.c ./check_map/fill_content_map.c ./check_map/check_content.c \
      get_next_line.c ./check_map/check_texture.c ./check_map/get_textures.c \
	  ./check_map/helpers.c ./check_map/get_color.c ./check_map/get_map.c ./check_map/check_player.c \
	  ./check_map/check_identifiers.c

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

