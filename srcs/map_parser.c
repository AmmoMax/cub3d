/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:48:41 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 00:31:46 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Добавляет в конец односвязного списка, который представляет карту, новую строку.
** Принимает строку и общий конфиг.
*/
static int		map_parser(char *line, m_config **config)
{
	t_list		*map_string;
	t_list		**map;
	char		*line_map;

	map = &((*config)->map);
	line_map = (char *)malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!line_map)
		return (ERR_MEMALLOC_MAP);
	map_string = ft_lstnew(ft_strcpy(line_map, line));
	if (!map_string)
	{
		cleanup_map(map);
		return (ERR_MEMALLOC_MAP);
	}
	return(ft_lstadd_back(map, map_string));
}

/*
** Общий обработчик строки карты. В зависимости от строки вызывает нужный валидатор.
** Сначала вызывает парсер карты, который записывает строку из файла в односвязный список.
** Принимает строку из файла и общий конфиг
*/
int				map_handler(char *line, m_config **config)
{
	m_config	*tmp;
	int			res;

	tmp = *config;
	if ((res = map_parser(line, config)) != 0)
	{
		print_err(res);
		return (res);
	}
	return (0);
}

/*
** Нормализует карту, дополняя кажду строку пробелами до длины самой длинной строки.
** Принимает указатель на карту и максимальную длину строки в карте.
*/
static void		normalize_map(char **map, int max_len)
{
	size_t		i;
	size_t		str_len;

	i = 0;
	while (map[i] != 0)
	{
		str_len = ft_strlen(map[i]);
		if (str_len < (size_t)max_len)
		{
			while (str_len < (size_t)max_len)
			{
				map[i][str_len] = ' ';
				str_len++;
			}
			map[i][str_len] = '\0';
		}
		i++;
	}
}

static void		*с_local_print_error(int err)
{
	print_err(err);
	return (NULL);
}

/*
** Конвертирует карту из формата односвязного списка в двумерный массив.
** Сохраняет в общий конфиг максимальный и минимальный x и y в двумерном массиве.
** Принимает указатель на первый элемент списка.
** Возвращает указатель на двумерный массив.
*/
char			**convert_map(t_list *head, m_config **config)
{
	char		**map;
	int			max_len;
	int			i;

	i = 0;
	max_len = max_len_line(head);
	(*config)->max_y = ft_lstsize(head);
	(*config)->max_x = max_len + 1;
	if (!(map = (char **)ft_calloc(ft_lstsize(head) + 1, sizeof(char *))))
		return (с_local_print_error(ERR_MEMALLOC_CONVERTMAP));
	if (!(map[0] = (char *)ft_calloc((max_len + 1) * ft_lstsize(head),
								sizeof(char))))
		return (с_local_print_error(ERR_MEMALLOC_CONVERTMAP));
	while (++i < (ft_lstsize(head)))
		map[i] = map[0] + i * (max_len + 1);
	i = 0;
	while (head->next)
	{
		ft_strcpy(map[i], head->content);
		i++;
		head = head->next;
	}
	ft_strcpy(map[i], head->content);
	normalize_map(map, max_len);
	return (map);
}
