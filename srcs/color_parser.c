/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 22:18:55 by amayor            #+#    #+#             */
/*   Updated: 2020/11/20 16:04:03 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
* Валидирует строку с кодом цвета в RGB
* Пример валидной строки: "F 220,100,0";
* Валидная строка:
*	Содержит любое количество пробелов между элементами
*	Начинается с буквы F или C
*	Содержит ровно 3 числа от 0 до 255
* TODO: Добавить обработку переполнения atoi
*/
static int		color_validator(char *line)
{
	size_t		i;
	size_t		num_cnt;
	char 		*tmp;
	size_t		flag_color;

	i = -1;
	num_cnt = 0;
	tmp = line;
	while(line[++i])
	{
		if ((line[i] == 'C' || line[i] == 'F') && line[i + 1] == ' ')
				flag_color = 1;
		else if (line[i] == ' ' || line[i] == ',' ||
				(ft_isdigit(line[i]) && ft_isdigit(line[i - 1])))
				;
		else if (ft_isdigit(line[i]) && !(ft_isdigit(line[i - 1])))
		{
			if (ft_atoi(tmp + i) > 255 || ft_atoi(tmp + i) < 0 || flag_color != 1)
				return (1);
			num_cnt++;
		}
		else
			return (1);
	}
	return (num_cnt == 3 ? 0 : 1);
}

static void		color_writer(char *line, color **color)
{
	size_t		i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && (line[i - 1] == ' ' || line[i - 1] == ','))
		{
			if ((*color)->red == -1)
				(*color)->red = ft_atoi(line + i);
			else if ((*color)->green == -1)
				(*color)->green = ft_atoi(line + i);
			else if ((*color)->blue == -1)
				(*color)->blue = ft_atoi(line + i);
			i++;
		}
		else
			i++;
	}
}

/*
* Парсит валидную строку, сохраняет данные в структуру и 
* адрес этой структуры записывает в общую структуру config
* C 100,255,255
*/
static int		color_parser(char *line, m_config **config)
{
	color		*floor_p;
	color		*ceiling_p;

	if (ft_strchr(line, 'C'))
	{
		if(!(ceiling_p  = (color *)(malloc(sizeof(color)))))
			return (ERR_MEMALLOC);
		ceiling_p->red = -1;
		ceiling_p->green = -1;
		ceiling_p->blue = -1;
		color_writer(line, &ceiling_p);
		(*config)->ceiling = ceiling_p;
	}
	if (ft_strchr(line, 'F'))
	{
		if (!(floor_p  = (color *)(malloc(sizeof(color)))))
			return (ERR_MEMALLOC);
		floor_p->red = -1;
		floor_p->green = -1;
		floor_p->blue = -1;
		color_writer(line, &floor_p);
		(*config)->floor = floor_p;
	}
	return (0);
}

int				color_handler(char *line, m_config **config)
{
	if (color_validator(line) == 0)
	{
		if (color_parser(line, config) != 0)
		{
			clean_config_no_map(config);
			return (ERR_MEMALLOC);
		}
	}
	else
		return (ERR_INVCOLOR);
	return (0);
}