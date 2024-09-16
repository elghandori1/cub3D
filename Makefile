NAME = cub3D
NAME_BONUS = cub3D_bonus
LIBFT = libft/libft.a

SRC = ./mandatory/main.c \
	  $(addprefix ./check_map/, check_map.c  check_content.c check_texture.c \
	  	get_textures.c helpers.c get_color.c get_map.c check_player.c check_identifiers.c check_walls.c fill_content_map.c helpe_free.c)  \
	  $(addprefix ./mandatory/Rendering/, raycasting.c utils.c utils2.c render_wall.c)\
	  $(addprefix ./mandatory/hooks/, moves.c move_player.c) \
	  $(addprefix ./helpers/, get_next_line.c)

SRC_BONUS = ./bonus/main_bonus.c \
	  $(addprefix ./check_map/, check_map.c  check_content.c check_texture.c \
	  	get_textures.c helpers.c get_color.c get_map.c check_player.c check_identifiers.c check_walls.c fill_content_map.c helpe_free.c)  \
	  $(addprefix ./bonus/minimap_bonus/, minimap_bonus.c)\
	  $(addprefix ./bonus/Rendering_bonus/, utils_bonus.c utils2_bonus.c render_bonus.c raycasting_bonus.c)\
	  $(addprefix ./bonus/hooks_bonus/, moves_bonus.c mouse_bonus.c player_bonus.c) \
	  $(addprefix ./helpers/, get_next_line.c)

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
