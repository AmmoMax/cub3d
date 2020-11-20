/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 22:09:19 by amayor            #+#    #+#             */
/*   Updated: 2020/11/20 15:25:21 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Парсит строку с путем к текстуре из файла и сохраняет ее в структуру конфига.
** TODO: добавить очищение памяти если память не выделилась под одну из строк
*/
static int	tex_parser(char *line, char flag, m_config **config)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!str)
		return (ERR_MEMALLOC);
	while (line[i] == ' ')
		i++;
	if(flag == 'N')
		(*config)->no_texture = ft_strcpy(str, line + i);
	else if(flag == 'S')
		(*config)->so_texture = ft_strcpy(str, line + i);
	else if(flag =='W')
		(*config)->we_texture = ft_strcpy(str, line + i);
	else if(flag == 'E')
		(*config)->ea_texture = ft_strcpy(str, line + i);
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
		return (ERR_PARSE_TEX);
}

int	texture_handler(char *line, m_config **config)
{
	if (tex_validator(line, config) == 1)
	{
		clean_config_no_map(config);
		return (ERR_MEMALLOC);
	}
	return (0);
}