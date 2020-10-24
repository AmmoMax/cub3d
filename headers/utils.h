/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:40:16 by amayor            #+#    #+#             */
/*   Updated: 2020/10/24 22:00:34 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
	int					*gamer_pos;
}						m_config;


int		res_handler(char *line, m_config **config);
int		texture_handler(char *line, m_config **config);
int		sprite_handler(char *line, m_config **config);
int		color_handler(char *line, m_config **config);
int		map_handler(char *line, m_config **config);
char	**convert_map(t_list **head);
int		map_validator(char **map, int len_map);