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

# Explicitly specify all object files
OBJS		= src/main.o \
			  src/init/init_game.o \
			  src/init/init_player.o \
			  src/parse/parse_file.o \
			  src/parse/parse_header.o \
			  src/parse/parse_map.o \
			  src/parse/parse_validate.o \
			  src/texture/texture_load.o \
			  src/input/input_key.o \
			  src/input/frame_hook.o \
			  src/free/free_game.o \
			  src/raycast/ray_cast.o \
			  src/raycast/ray_march.o \
			  src/raycast/ray_render.o \
			  src/raycast/ray_setup.o \
			  src/raycast/ray_wall.o

LIBS		= -Lsrc/libft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	@make -C src/libft

$(MLX):
	@make -C minilibx-linux

# Individual compilation rules for each object file
src/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/init/init_game.o: src/init/init_game.c
	$(CC) $(CFLAGS) -c src/init/init_game.c -o src/init/init_game.o

src/init/init_player.o: src/init/init_player.c
	$(CC) $(CFLAGS) -c src/init/init_player.c -o src/init/init_player.o

src/parse/parse_file.o: src/parse/parse_file.c
	$(CC) $(CFLAGS) -c src/parse/parse_file.c -o src/parse/parse_file.o

src/parse/parse_header.o: src/parse/parse_header.c
	$(CC) $(CFLAGS) -c src/parse/parse_header.c -o src/parse/parse_header.o

src/parse/parse_map.o: src/parse/parse_map.c
	$(CC) $(CFLAGS) -c src/parse/parse_map.c -o src/parse/parse_map.o

src/parse/parse_validate.o: src/parse/parse_validate.c
	$(CC) $(CFLAGS) -c src/parse/parse_validate.c -o src/parse/parse_validate.o

src/texture/texture_load.o: src/texture/texture_load.c
	$(CC) $(CFLAGS) -c src/texture/texture_load.c -o src/texture/texture_load.o

src/input/input_key.o: src/input/input_key.c
	$(CC) $(CFLAGS) -c src/input/input_key.c -o src/input/input_key.o

src/input/frame_hook.o: src/input/frame_hook.c
	$(CC) $(CFLAGS) -c src/input/frame_hook.c -o src/input/frame_hook.o

src/free/free_game.o: src/free/free_game.c
	$(CC) $(CFLAGS) -c src/free/free_game.c -o src/free/free_game.o

src/raycast/ray_cast.o: src/raycast/ray_cast.c
	$(CC) $(CFLAGS) -c src/raycast/ray_cast.c -o src/raycast/ray_cast.o

src/raycast/ray_march.o: src/raycast/ray_march.c
	$(CC) $(CFLAGS) -c src/raycast/ray_march.c -o src/raycast/ray_march.o

src/raycast/ray_render.o: src/raycast/ray_render.c
	$(CC) $(CFLAGS) -c src/raycast/ray_render.c -o src/raycast/ray_render.o

src/raycast/ray_setup.o: src/raycast/ray_setup.c
	$(CC) $(CFLAGS) -c src/raycast/ray_setup.c -o src/raycast/ray_setup.o

src/raycast/ray_wall.o: src/raycast/ray_wall.c
	$(CC) $(CFLAGS) -c src/raycast/ray_wall.c -o src/raycast/ray_wall.o

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
