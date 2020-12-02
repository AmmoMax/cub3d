/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:40:16 by amayor            #+#    #+#             */
/*   Updated: 2020/11/28 23:03:21 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <fcntl.h>

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_config
{
	int			x;
	int			y;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*s_texture;
	t_color		*floor;
	t_color		*ceiling;
	t_list		*map;
	char		**flat_map;
	int			max_x;
	int			max_y;
	int			count_res;
	int			count_ntex;
	int			count_stex;
	int			count_wtex;
	int			count_etex;
	int			count_sprtex;
	int			count_clrf;
	int			count_clrc;
	int			count_map;
}				t_config;

int				res_handler(char *line, t_config **config);
int				texture_handler(char *line, t_config **config);
int				sprite_handler(char *line, t_config **config);
int				color_handler(char *line, t_config **config);
int				map_handler(char *line, t_config **config);
int				map_validator(char **map, int len_map);
t_config		*read_config (char *path);
void			cleanup_map(t_list **map_head);
int				start_cub3d(char *path, char *save_flag);
void			cleanup_flat_map(char **map);
char			**convert_map(t_list *head, t_config **config);
void			clean_config_all(t_config **p_config);
void			clean_config_no_map(t_config **p_config);
void			print_err(int err_type);
int				check_player(int flag);
int				check_path_tex(t_config *config);
void			set_texture(t_config **config, char *str,
							char *line, char flag);
int				color_validator(char *line);
int				max_len_line(t_list *head);
int				local_print_error(int err);

#endif
