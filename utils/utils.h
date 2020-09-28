/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:40:16 by amayor            #+#    #+#             */
/*   Updated: 2020/09/23 23:33:03 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct			maze_config
{
	int					x;	
	int					y;	
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

// typedef struct			resolution
// {
// 	int					x;
// 	int					y;
// }						m_resolution;

int		res_handler(char *line, m_config **config);