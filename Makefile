NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinc -Isrc/libft -Iminilibx-linux
LIBFT		= src/libft/libft.a
MLX			= minilibx-linux/libmlx.a

# Explicitly specify all source files
SRCS		= src/main.c \
			  src/init/init_game.c \
			  src/init/init_player.c \
			  src/parse/parse_file.c \
			  src/parse/parse_header.c \
			  src/parse/parse_map.c \
			  src/parse/parse_validate.c \
			  src/texture/texture_load.c \
			  src/input/input_key.c \
			  src/input/frame_hook.c \
			  src/free/free_game.c \
			  src/raycast/ray_cast.c \
			  src/raycast/ray_march.c \
			  src/raycast/ray_render.c \
			  src/raycast/ray_setup.c \
			  src/raycast/ray_wall.c

# Derive object files from source files
OBJS		= $(SRCS:.c=.o)

LIBS		= -Lsrc/libft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	@make -C src/libft

$(MLX):
	@make -C minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C src/libft clean
	@make -C minilibx-linux clean
	@rm -f $(OBJS)

fclean: clean
	@make -C src/libft fclean
	@rm -f $(NAME)

bonus: all

re: fclean all

.PHONY: all clean fclean re bonus
