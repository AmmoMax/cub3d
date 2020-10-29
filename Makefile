# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/21 23:12:54 by amayor            #+#    #+#              #
#    Updated: 2020/10/29 19:01:50 by amayor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus

COMPILER = clang
NAME = cub3D
HEADER_FILES_DIR = headers
FLAGS = -Wall -Wextra -Werror -g3
LIBFT_DIR = libft
LIBFT_PATH = LIBFT_DIR/libft.a
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

override OBJ_ALL ?=$(OBJ_FILES)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "[INFO] Make libft in [$(LIBFT_PATH)] dir"
	$(MAKE) -C $(LIBFT_DIR)
	$(COMPILER) $(FLAGS) -I $(HEADER_FILES_DIR) $(addprefix srcs/, $(SRC_FILES) ) -L $(LIBFT_DIR) -lft