/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:40:16 by amayor            #+#    #+#             */
/*   Updated: 2020/11/14 16:45:35 by amayor           ###   ########.fr       */
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
	int					max_x;
	int					max_y;
}						m_config;

int			res_handler(char *line, m_config **config);
int			texture_handler(char *line, m_config **config);
int			sprite_handler(char *line, m_config **config);
int			color_handler(char *line, m_config **config);
int			map_handler(char *line, m_config **config);
int			map_validator(char **map, int len_map);
m_config	*read_config (char *path);
void		cleanup_map(m_config *config);
int			start_cub3d(char *path, char *save_flag);
void		cleanup_flat_map(char **map);
char		**convert_map(t_list *head, m_config **config);

#endif