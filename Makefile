# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/21 23:12:54 by amayor            #+#    #+#              #
#    Updated: 2020/11/29 20:10:03 by amayor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = cub3D
FLAGS = -Wall -Wextra -Werror -g3
COMPILER = clang
LIBS = -L$(LIBFT_DIR) -L$(MLX_DIR) -lft -lmlx_Linux
HEADER_FILES_DIR = headers
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux
SRC_DIR = ./srcs
OBJ_DIR = obj
LIBFT_PATH = $(LIBFT_DIR)/libft.a
SRC_FILES = config_parser.c \
			resolution_parser.c \
			textures_parser.c \
			sprite_parser.c \
			color_parser.c \
			map_parser.c \
			map_validator.c \
			clean.c \
			engine.c \
			main.c \
			g_flat_map.c \
			g_common_utils.c \
			graphics_engine.c \
			g_hooks.c \
			rays_utils.c \
			textures.c \
			sprites_utils.c \
			sprites.c \
			save_bmp.c \
			g_clean.c \
			error_handler.c \
			parser_utils.c \
			parser_utils_p2.c \
			g_common_utils_p2.c \
			g_3d_map.c


SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))


all:  $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ_FILES)
	@make -C $(MLX_DIR)
	@echo "Compile mlx lib!"
	@make -C $(LIBFT_DIR)
	@echo "Compile libft!"
	@echo "Compile $(NAME)"
	$(COMPILER) $(FLAGS) $(OBJ_FILES) -I $(HEADER_FILES_DIR) $(LIBS) -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_FILES): $(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(COMPILER) $(FLAGS) -I $(HEADER_FILES_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@echo "Run clean."
	@rm -rf $(OBJ_FILES)
	@echo "Delete object files : [$(OBJ_FILES)]!"
	@rm -f screenshot.bmp
	@echo "Delete screenshot.bmp"

fclean: clean
	@rm -f $(NAME)
	@echo "Delete binary $(NAME)"

re: fclean all

run:
	./cub3D maps/basic_map.cub

bonus: all