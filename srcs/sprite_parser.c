/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:22:19 by amayor            #+#    #+#             */
/*   Updated: 2020/11/20 15:43:57 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
* Валидирует и записывает в конфиг строку со спрайтом.
* Валидная строка: S ./path_to_the_sprite_texture
* Невалидная строка: X  S ./path_to_the_sprite_texture
*/
static int	sprite_validator(char *line)
{
	size_t	i;
	size_t	flag_s;
	size_t	flag_path;

	i = 0;
	flag_s = 0;
	flag_path = 0;

	while (line[i])
		if (line[i] == ' ')
			i++;
		else if (line[i] == 'S' && (line[i + 1] == ' ' || line[i + 1] == 'S'))
		{
			flag_s++;
			i++;
		}
		else if (line[i + 1] == ' ' || line[i + 1] == '\0')
		{
			flag_path++;
			i++;
		}
		else
			i++;
	return ((flag_s == 1 && flag_path == 1) ? 0 : ERR_INVMAP);
}

/*
*Принимает уже валидную строку, парсит и сохраняет ее в структуру конфига.
*/
static int	sprite_parser(char *line, m_config **config)
{
	size_t	i;
	char *str;

	str = (char *)malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!str)
		return (ERR_MEMALLOC);
	i = 0;
	while(line[i] == ' ' || line[i] == 'S')
		i++;
	(*config)->s_texture = ft_strcpy(str, line + i);
	return (0);
}

int			sprite_handler(char *line, m_config **config)
{
	if (sprite_validator(line) == 0)
		if (sprite_parser(line, config) != 0)
		{
			clean_config_no_map(config);
			return (ERR_MEMALLOC);
		}
	return (0);
}