/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 22:09:19 by amayor            #+#    #+#             */
/*   Updated: 2020/11/26 14:09:15 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Парсит строку с путем к текстуре из файла и сохраняет ее в структуру конфига.
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
	set_texture(config, str, line + i, flag);
	return (0);
}

static int	local_print_err(int err)
{
	print_err(err);
	return (err);
}

static int	get_tex_parser(m_config **config, char *line, size_t i)
{
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		if ((*config)->count_stex == 0)
			return (tex_parser(&line[i + 2], 'S', config));
		else
			return (local_print_err(ERR_DOUBLE_TEX));
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		if ((*config)->count_ntex == 0)
			return (tex_parser(&line[i + 2], 'N', config));
		else
			return (local_print_err(ERR_DOUBLE_TEX));
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		if ((*config)->count_wtex == 0)
			return (tex_parser(&line[i + 2], 'W', config));
		else
			return (local_print_err(ERR_DOUBLE_TEX));
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		if ((*config)->count_etex == 0)
			return (tex_parser(&line[i + 2], 'E', config));
		else
			return (local_print_err(ERR_DOUBLE_TEX));
	else
		return (local_print_err(ERR_INVLINE_TEX));
}

static int	tex_validator_v2(char *line, m_config **config)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (get_tex_parser(config, line, i));
}

int			texture_handler(char *line, m_config **config)
{
	int	res;

	if ((res = tex_validator_v2(line, config)) == ERR_MEMALLOC)
	{
		clean_config_no_map(config);
		print_err(ERR_MEMALLOC_TEXPARSER);
		return (ERR_MEMALLOC);
	}
	else
		return (res);
}
