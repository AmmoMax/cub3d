/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 22:09:19 by amayor            #+#    #+#             */
/*   Updated: 2020/09/29 22:30:01 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/utils.h"

static int	tex_parser(char *line, char flag, m_config **config)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if(flag == 'N')
		(*config)->no_texture = line + i;
	else if(flag == 'S')
		(*config)->so_texture = line + i;
	else if(flag =='W')
		(*config)->we_texture = line + i;
	else if(flag == 'E')
		(*config)->ea_texture = line + i;
	return (0);
}

static int	tex_validator(char *line, m_config **config)
{
	size_t	i;
	char	*res;

	i = 0;
	if((res = ft_strnstr(line, "NO", ft_strlen(line))))
		return (tex_parser(res + 2, 'N', config));
	else if((res = ft_strnstr(line, "SO", ft_strlen(line))))
		return (tex_parser(res + 2, 'S', config));
	else if((res = ft_strnstr(line, "WE", ft_strlen(line))))
		return (tex_parser(res + 2, 'W', config));
	else if((res = ft_strnstr(line, "EA", ft_strlen(line))))
		return (tex_parser(res + 2, 'E', config));
	else
		return (1);
}

int	texture_handler(char *line, m_config **config)
{
	if (tex_validator(line, config) == 1)
		return (1);
	return (0);
}