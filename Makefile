NAME = cub3D
LIBFT = libft/libft.a

SRC = main.c ./check_map/check_map.c ./check_map/fill_content_map.c ./check_map/check_content.c \
      get_next_line.c ./check_map/check_texture.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror 

%.o : %.c
	$(CC) $(CFLAGS) -c $? -o $@

all : $(NAME)

$(LIBFT):
	make -C libft

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJ)
	make clean -C libft

fclean:
	rm -rf $(NAME) $(OBJ)
	make fclean -C libft

clear:
	clear

re: fclean all clean  clear

