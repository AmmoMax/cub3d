/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:40:16 by amayor            #+#    #+#             */
/*   Updated: 2020/11/26 23:30:50 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct			s_color
{
	int					red;
	int					green;
	int					blue;
}						t_color;

typedef struct			maze_config_t
{
	int					x;
	int					y;
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	char				*s_texture;
	t_color				*floor;
	t_color				*ceiling;
	t_list				*map;
	int					*gamer_pos;
}						m_config;

int		res_handler(char *line, m_config **config);
int		texture_handler(char *line, m_config **config);
