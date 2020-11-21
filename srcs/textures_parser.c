/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 22:09:19 by amayor            #+#    #+#             */
/*   Updated: 2020/11/21 22:34:21 by amayor           ###   ########.fr       */
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
	{
		(*config)->no_texture = ft_strcpy(str, line + i);
		(*config)->count_ntex = 1;
	}
	else if(flag == 'S')
	{
		(*config)->so_texture = ft_strcpy(str, line + i);
		(*config)->count_stex = 1;
	}
	else if(flag =='W')
	{
		(*config)->we_texture = ft_strcpy(str, line + i);
		(*config)->count_wtex = 1;
	}
	else if(flag == 'E')
	{
		(*config)->ea_texture = ft_strcpy(str, line + i);
		(*config)->count_etex = 1;
	}
	return (0);
}

// static int	tex_validator(char *line, m_config **config)
// {
// 	size_t	i;
// 	char	*res;

// 	i = 0;
// 	if((res = ft_strnstr(line, "NO", ft_strlen(line))))
// 		return (tex_parser(res + 2, 'N', config));
// 	else if((res = ft_strnstr(line, "SO", ft_strlen(line))))
// 		return (tex_parser(res + 2, 'S', config));
// 	else if((res = ft_strnstr(line, "WE", ft_strlen(line))))
// 		return (tex_parser(res + 2, 'W', config));
// 	else if((res = ft_strnstr(line, "EA", ft_strlen(line))))
// 		return (tex_parser(res + 2, 'E', config));
// 	else
// 	{
// 		print_err(ERR_INVLINE_CONF);
// 		return (ERR_PARSE_TEX);
// 	}
// }

static int	local_print_err(int err)
{
	print_err(err);
	return (err);
}

static int	tex_validator_v2(char *line, m_config **config)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		if ((*config)->count_stex == 0)
			return (tex_parser(&line[i + 2], 'S', config));
		else
			local_print_err(ERR_DOUBLE_TEX);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		if ((*config)->count_ntex == 0)
			return (tex_parser(&line[i + 2], 'N', config));
		else
			local_print_err(ERR_DOUBLE_TEX);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		if ((*config)->count_wtex == 0)
			return (tex_parser(&line[i + 2], 'W', config));
		else
			local_print_err(ERR_DOUBLE_TEX);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		if ((*config)->count_etex == 0)
			return (tex_parser(&line[i + 2], 'E', config));
		else
			local_print_err(ERR_DOUBLE_TEX);
	else
		local_print_err(ERR_INVLINE_TEX);
	return (1);
}

int		texture_handler(char *line, m_config **config)
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