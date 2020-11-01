# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/21 23:12:54 by amayor            #+#    #+#              #
#    Updated: 2020/10/31 21:32:00 by amayor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus

NAME = cub3D
FLAGS = -Wall -Wextra -Werror -g3
COMPILER = clang
LIBS = -L$(LIBFT_DIR) -L$(MLX_DIR) -lft -lmlx_Linux
HEADER_FILES_DIR = ./headers
LIBFT_DIR = ./libft
MLX_DIR = ./mlx
SRC_DIR = ./srcs
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
			graphics_engine.c

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ_FILES = $(SRC_FILES:.c=.o)

# override OBJ_ALL ?=$(OBJ_FILES)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	# $(COMPILER) $(FLAGS) $(LIBS) $(OBJ_FILES) -I $(HEADER_FILES_DIR) -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
	$(COMPILER) $(FLAGS) $(OBJ_FILES) -I $(HEADER_FILES_DIR) $(LIBS) -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_FILES): $(SRCS)
	$(COMPILER) $(FLAGS) -I $(HEADER_FILES_DIR) -c $(SRCS)
# %.o: %.c
	# @echo "1111" 
# 	$(COMPILER) $(FLAGS) -I $(HEADER_FILES_DIR) -O3 -c $< -o $@

# $(NAME): $(OBJ_ALL)
# 	@echo "[INFO] Make libft in [$(LIBFT_DIR)] dir"
# 	$(MAKE) -C $(LIBFT_DIR)
# 	cp $(LIBFT_PATH) $(EXT_LIBS)
# 	$(COMPILER) -L$(EXT_LIBS) -lft -lmlx_Linux -I$(HEADER_FILES_DIR) -L/usr/lib -lXext -lX11 -lm -lz -c $(addprefix srcs/, $(SRC_FILES) )

# %.o: %.c
# 	@echo "1111" 