/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:48:41 by amayor            #+#    #+#             */
/*   Updated: 2020/10/28 23:23:49 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Добавляет в конец односвязного списка, который представляет карту, новую строку.
** Принимает строку и общий конфиг.
*/
static int	map_parser(char *line, m_config **config)
{
	t_list	*map_string;
	t_list	**map;

	map = &(*config)->map;
	map_string = ft_lstnew(line);
	if (!map_string)
	{
		cleanup_map(config);
		return (ERR_MEMALLOC);
	}
	return(ft_lstadd_back(map, map_string));
}

static int	max_len_line(t_list *head)
{
	size_t max_len;
	size_t	len;

	max_len = 0;
	len = 0;
	while (head->next)
	{
		len = ft_strlen(head->content);
		if (len > max_len)
			max_len = len;
		head = head->next;
	}
	return (max_len);
}
/*
** Общий обработчик строки карты. В зависимости от строки вызывает нужный валидатор.
** Сначала вызывает парсер карты, который записывает карту из файла в односвязный список.
** Потом вызывает конвертор карты из односвязного списка в двумерный массив.
** Потом вызывает валидатор карты, который валидирует карту.
** Принимает строку из файла и общий конфиг
*/
int				map_handler(char *line, m_config **config)
{
	m_config	*tmp;
	int			len_map;

	tmp = *config;
	if (map_parser(line, config) != 0)
		return (ERR_MEMALLOC);
	tmp->flat_map = convert_map(tmp->map);
	if (!(tmp->flat_map))
		return (ERR_MEMALLOC);
	len_map = ft_lstsize(tmp->map);
	if (map_validator(tmp->flat_map, len_map) != 0)
		return (ERR_INVMAP);
}

/*
* Нормализует карту, дополняя кажду строку пробелами до длины самой длинной строки.
* Принимает указатель на карту и максимальную длину строки в карте.
*/
static void	normalize_map(char **map, int max_len)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	while(map[i] != 0)
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

/*
* Конвертирует карту из формата односвязного списка в двумерный массив.
* Принимает указатель на первый элемент списка.
* Возвращает указатель на двумерный массив.
*/
char		**convert_map(t_list *head)
{
	char 	**map;
	int		max_len;
	int		i;

	i = 0;
	max_len = max_len_line(head);
	if (!(map = (char **)ft_calloc(ft_lstsize(head) + 1, sizeof(char *))))
		return (NULL); // TODO: скорее всего изменить возвращаемое значение из за типа функции
	if (!(map[0] = (char *)ft_calloc((max_len + 1) * ft_lstsize(head),sizeof(char))))
		return (NULL);
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
