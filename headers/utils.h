/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:40:16 by amayor            #+#    #+#             */
/*   Updated: 2020/10/29 23:07:22 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <fcntl.h>

typedef struct			color_t
{
	int					red;
	int					green;
	int					blue;
}						color;

typedef struct			maze_config
{
	int					x;	
	int					y;	
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	char				*s_texture;
	color				*floor;
	color				*ceiling;
	t_list				*map;
	char				**flat_map;
	int					*gamer_pos;
}						m_config;

typedef struct 			s_data
{
	void 				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_data;

typedef struct			s_vars
{
	void				*mlx;
	void				*win;
}						t_vars;

typedef struct 			s_world
{
	t_vars				*vars;
	t_data				*img;
	int					x;
	int					y;
}						t_world;

int			res_handler(char *line, m_config **config);
int			texture_handler(char *line, m_config **config);
int			sprite_handler(char *line, m_config **config);
int			color_handler(char *line, m_config **config);
int			map_handler(char *line, m_config **config);
char		**convert_map(t_list *head);
int			map_validator(char **map, int len_map);
m_config	*read_config (char *path);
void		cleanup_map(m_config *config);
int			start_cub3d(char *path, char *save_flag);
void		cleanup_flat_map(char **map);

#endif