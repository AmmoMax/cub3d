/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 22:39:43 by amayor            #+#    #+#             */
/*   Updated: 2020/10/28 23:33:03 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Получает строку из файла и отправляет в нужный обработчик.
** Возвращает код, который вернул обработчик.
*/
int			line_handler(char *line, m_config **config)
{
	size_t	len;

	len = ft_strlen(line);
	if (ft_strchr(line, 'R'))
		return (res_handler(line, config));
	else if (ft_strnstr(line, "NO", len) || ft_strnstr(line, "SO", len) ||
			 ft_strnstr(line, "WE", len) || ft_strnstr(line, "EA", len))
		return (texture_handler(line, config));
	else if (ft_strchr(line, 'S'))
		return (sprite_handler(line, config));
	else if (ft_strchr(line, 'F')|| ft_strchr(line, 'C'))
		return(color_handler(line, config));
	else if (ft_strchr(line, '1')) // TODO: более точное условие строки с картой
		return (map_handler(line, config));
	else if (line[0] == '\n' || line[0] == 0)
		return (OK);
	else
		return (OK);
}

m_config			*read_config (char *path)
{
	int				fd;
	char			*line;
	m_config		*config_p;
	int				res_line_handler;

	line = NULL;
	if (!(config_p = ft_calloc(1, sizeof(m_config))) ||
			(fd = open(path, O_RDONLY)) < 0)
			return (NULL);
	while (get_next_line(fd, &line)) // malloc line
	{
		res_line_handler = line_handler(line, &config_p);
		if (res_line_handler != 0)
			return (res_line_handler);
		//TODO: добавить выделение памяти для каждой строки конфига, чтобы каждый раз очищать line
		// free(line);
	}
	return (config_p);
}
