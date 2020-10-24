/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:48:41 by amayor            #+#    #+#             */
/*   Updated: 2020/10/24 22:06:41 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/utils.h"

/*
* Добавляет в конец односвязного списка, который представляет карту, новую строку.
* Принимает строку и общий конфиг.
* TODO: Добавить проверку выделения памяти под структуру и очистку
*/
static int	map_parser(char *line, m_config **config)
{
	t_list	*map_string;
	t_list	**map;

	map = &(*config)->map;
	map_string = ft_lstnew(line);
	if (map_string)
		return(ft_lstadd_back(map, map_string));
	else
		return (1);
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
* Общий обработчик строки карты. В зависимости строки вызывает нужный валидатор.
* Принимает указатель на строку и флаг линии - по нему опрделяется первая строка,
* последняя и все остальные.
* Возвращает код: 1 - ошибка, 0 - ОК
*/
int			map_handler(char *line, m_config **config)
{
	return (map_parser(line, config));
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
char		**convert_map(t_list **map_head)
{
	char 	**map;
	int		max_len;
	int		i;
	t_list	*head;

	i = 1;
	head = *map_head;
	max_len = max_len_line(head);
	if (!(map = (char **)ft_calloc(ft_lstsize(head) + 1, sizeof(char *))))
		return (NULL);
	if (!(map[0] = (char *)ft_calloc((max_len + 1) * ft_lstsize(head),sizeof(char))))
		return (NULL);
	while (i < (ft_lstsize(head)))
	{
		map[i] = map[0] + i * (max_len + 1);
		i++;
	}
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
