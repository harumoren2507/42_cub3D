# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maono <maono@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/22 05:41:46 by maono             #+#    #+#              #
#    Updated: 2026/06/22 06:02:42 by maono            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= cc
MAKEFLAGS	+= --no-print-directory

LIBFT_DIR	= src/libft
MLX_DIR		= minilibx-linux
MLX_URL		= https://cdn.intra.42.fr/document/document/47450/minilibx-linux.tgz
OBJ_DIR		= .obj
DEP_DIR		= .dep

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a

CFLAGS		= -Wall -Wextra -Werror
CPPFLAGS	= -Iinc -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS		= -lft -lmlx -lXext -lX11 -lm
DEPFLAGS	= -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d

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

OBJS		= $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
DEPS		= $(SRCS:src/%.c=$(DEP_DIR)/%.d)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR):
	@echo "Downloading minilibx..."
	@wget -q $(MLX_URL) -O minilibx-linux.tgz
	@tar -xzf minilibx-linux.tgz
	@$(RM) minilibx-linux.tgz
	@echo "minilibx downloaded!"

$(MLX): | $(MLX_DIR)
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D) $(DEP_DIR)/$(dir $*)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@[ -f $(MLX) ] && $(MAKE) -C $(MLX_DIR) clean || true
	@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	@$(RM) $(LIBFT) $(MLX) $(NAME)

bonus: all

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re bonus

-include $(DEPS)
