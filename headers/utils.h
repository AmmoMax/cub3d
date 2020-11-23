/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:40:16 by amayor            #+#    #+#             */
/*   Updated: 2020/11/23 23:49:23 by amayor           ###   ########.fr       */
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
	int					count_res;
	int					count_ntex;
	int					count_stex;
	int					count_wtex;
	int					count_etex;
	int					count_sprtex;
	int					count_clrf;
	int					count_clrc;
}						m_config;


int			res_handler(char *line, m_config **config);
int			texture_handler(char *line, m_config **config);
int			sprite_handler(char *line, m_config **config);
int			color_handler(char *line, m_config **config);
int			map_handler(char *line, m_config **config);
int			map_validator(char **map, int len_map);
m_config	*read_config (char *path);
void		cleanup_map(t_list **map_head);
int			start_cub3d(char *path, char *save_flag);
void		cleanup_flat_map(char **map);
char		**convert_map(t_list *head, m_config **config);
void		clean_config_all(m_config **p_config);
void		clean_config_no_map(m_config **p_config);
void		print_err(int err_type);
int			check_player(int flag);
int			check_path_tex(m_config *config);
void		set_texture(m_config **config, char *str,
					char *line, char flag, size_t i);
int			color_validator(char *line);

#endif
