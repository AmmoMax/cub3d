/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 22:18:55 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 00:34:41 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

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

static color	*set_color_tex(char tex, char *line)
{
	color		*ceiling_p;
	color		*floor_p;

	if (tex == 'C')
	{
		if(!(ceiling_p  = (color *)(malloc(sizeof(color)))))
			return (NULL);
		ceiling_p->red = -1;
		ceiling_p->green = -1;
		ceiling_p->blue = -1;
		color_writer(line, &ceiling_p);
		return (ceiling_p);
	}
	else
	{
		if (!(floor_p  = (color *)(malloc(sizeof(color)))))
			return (NULL);
		floor_p->red = -1;
		floor_p->green = -1;
		floor_p->blue = -1;
		color_writer(line, &floor_p);
		return (floor_p);
	}
}

/*
** Парсит валидную строку, сохраняет данные в структуру и
** адрес этой структуры записывает в общую структуру config
** C 100,255,255
*/
static int		color_parser(char *line, m_config **config)
{
	color		*color_p;

	if (ft_strchr(line, 'C'))
	{
		if ((*config)->count_clrc != 0)
			return (local_print_error(ERR_DOUBLE_C_COLOR));
		if(!(color_p = set_color_tex('C', line)))
			return (ERR_MEMALLOC);
		(*config)->ceiling = color_p;
		(*config)->count_clrc = 1;
	}
	if (ft_strchr(line, 'F'))
	{
		if ((*config)->count_clrf != 0)
			return (local_print_error(ERR_DOUBLE_F_COLOR));
		if(!(color_p = set_color_tex('F', line)))
			return (ERR_MEMALLOC);
		(*config)->floor = color_p;
		(*config)->count_clrf = 1;
	}
	return (0);
}

int				color_handler(char *line, m_config **config)
{
	int			res;
	if ((res = color_validator(line)) == 0)
	{
		if ((res = color_parser(line, config)) == ERR_MEMALLOC_COLORPARSER)
		{
			clean_config_no_map(config);
			print_err(res);
			return (res);
		}
		else
			return(res);
	}
	else
	{
		print_err(res);
		return (res);
	}
	return (0);
}
