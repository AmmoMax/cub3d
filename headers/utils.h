/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:40:16 by amayor            #+#    #+#             */
/*   Updated: 2020/09/15 21:46:13 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct			maze_config
{
	struct resolution	*m_resolution;
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	char				*s_texture;
	int					*color_floor;
	int					*ceilling_floor;
	char				**map;
	int					*gamer_pos;
}						m_config;

typedef struct			resolution
{
	int					x;
	int					y;
}						m_resolution;

void		res_handler(char *line, m_resolution **res);