/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 22:39:43 by amayor            #+#    #+#             */
/*   Updated: 2020/11/28 20:39:17 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Получает строку из файла и отправляет в нужный обработчик.
** Возвращает код, который вернул обработчик.
*/

int					line_handler(char *line, t_config **config)
{
	size_t			len;

	len = ft_strlen(line);
	if (ft_strchr(line, 'R'))
		return (res_handler(line, config));
	else if (ft_strnstr(line, "NO", len) || ft_strnstr(line, "SO", len) ||
			ft_strnstr(line, "WE", len) || ft_strnstr(line, "EA", len))
		return (texture_handler(line, config));
	else if (ft_strnstr(line, "S ", len))
		return (sprite_handler(line, config));
	else if (ft_strchr(line, 'F') || ft_strchr(line, 'C'))
		return (color_handler(line, config));
	else if (ft_strchr(line, '1'))
	{
		(*config)->count_map = 1;
		return (map_handler(line, config));
	}
	else if ((line[0] == '\n' && (*config)->count_map == 0) ||
		(line[0] == 0 && (*config)->count_map == 0))
		return (0);
	else
	{
		print_err(ERR_INVLINE_CONF);
		return (1);
	}
}

static t_config		*init_config(void)
{
	t_config		*config;

	if (!(config = (t_config *)ft_calloc(1, sizeof(t_config))))
		return (NULL);
	config->count_wtex = 0;
	config->count_etex = 0;
	config->count_stex = 0;
	config->count_ntex = 0;
	config->count_res = 0;
	config->count_sprtex = 0;
	config->count_clrc = 0;
	config->count_clrf = 0;
	config->count_map = 0;
	return (config);
}

static void			*local_clean(t_config **config, char **line, int err)
{
	free(*config);
	free(*line);
	print_err(err);
	return (NULL);
}

t_config			*read_config(char *path)
{
	int				fd;
	char			*line;
	t_config		*config_p;
	int				res_line_handler;

	line = NULL;
	fd = open(path, O_RDONLY);
	if (!(config_p = init_config()) || fd < 0)
	{
		print_err(ERR_OFILE);
		return (NULL);
	}
	while (get_next_line(fd, &line))
	{
		res_line_handler = line_handler(line, &config_p);
		if (res_line_handler != 0)
			return (local_clean(&config_p, &line, ERR_PARSE_CFILE));
		free(line);
	}
	res_line_handler = line_handler(line, &config_p);
	if (res_line_handler != 0)
		return (local_clean(&config_p, &line, ERR_PARSE_CFILE));
	free(line);
	return (config_p);
}
