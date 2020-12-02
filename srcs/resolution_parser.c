/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:28:35 by amayor            #+#    #+#             */
/*   Updated: 2020/11/28 15:00:06 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Парсинг строки с разрешением экрана из файла конфига.
** На вход принимает только ВАЛИДНУЮ строку.
** Разрешение экрана строка типа: R 1920 1080
*/

static void	res_parser(char *line, t_config **config)
{
	size_t	i;
	size_t	flag_x;
	char	*tmp;

	i = 1;
	flag_x = 0;
	tmp = line;
	(*config)->count_res++;
	while (line[i])
		if (line[i] == ' ' || (ft_isdigit(line[i]) && ft_isdigit(line[i - 1])))
			i++;
		else if (ft_isdigit(line[i]) && !ft_isdigit(line[i - 1]))
		{
			if (flag_x == 0)
			{
				(*config)->x = ft_atoi(tmp + i);
				flag_x = 1;
			}
			else
				(*config)->y = ft_atoi(tmp + i);
			i++;
		}
		else
			i++;
}

/*
** Валидирует строку.
** Валидная строка: начинается с R,
** потом идет любое количество пробелов и два числа > 0,
** разделенные любым кол-вом пробелов.
** Возвращает 0 если строка валидна, и 1 если невалидна.
*/

static int	res_validator(char *line)
{
	size_t	i;
	size_t	nbr_count;
	int		flag_r;

	i = -1;
	nbr_count = 0;
	flag_r = 0;
	while (line[++i])
	{
		if (line[i] == ' ' || (ft_isdigit(line[i]) && ft_isdigit(line[i + 1])))
			;
		else if (line[i] == 'R' && line[i + 1] == ' ' && flag_r == 0)
			flag_r = 1;
		else if (ft_isdigit(line[i]) && (line[i + 1] == ' ' ||
					line[i + 1] == '\0') && nbr_count <= 2)
			nbr_count++;
		else
			return (1);
	}
	return ((nbr_count != 2 || flag_r != 1) ? 1 : 0);
}

/*
** Принимает необработанную строку от парсера файла конфигурации.
** Валидирует и парсит строку, сохраняет разрешение в общую структуру.
** Если строка невалидна - возвращает ошибку.
*/

int			res_handler(char *line, t_config **config)
{
	if (res_validator(line) == 0)
	{
		if ((*config)->count_res == 0)
		{
			res_parser(line, config);
			return (0);
		}
		else
		{
			print_err(ERR_DOUBLE_RES);
			return (1);
		}
	}
	else
	{
		print_err(ERR_INVRES);
		return (1);
	}
}

int			check_path_tex(t_config *config)
{
	int		fd;

	if ((fd = open(config->no_texture, O_RDONLY)) < 0)
	{
		print_err(ERR_INCPATH_TEX);
		return (ERR_INCPATH_TEX);
	}
	else if ((fd = open(config->so_texture, O_RDONLY)) < 0)
	{
		print_err(ERR_INCPATH_TEX);
		return (ERR_INCPATH_TEX);
	}
	else if ((fd = open(config->ea_texture, O_RDONLY)) < 0)
	{
		print_err(ERR_INCPATH_TEX);
		return (ERR_INCPATH_TEX);
	}
	else if ((fd = open(config->we_texture, O_RDONLY)) < 0)
	{
		print_err(ERR_INCPATH_TEX);
		return (ERR_INCPATH_TEX);
	}
	else
		return (0);
}
