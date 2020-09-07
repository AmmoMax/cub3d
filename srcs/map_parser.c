/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 22:39:43 by amayor            #+#    #+#             */
/*   Updated: 2020/09/07 23:11:58 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <fcntl.h>
#include <stdio.h>
#define ERROR 1
#define OK 0

/*
* Парсинг строки с разрешением экрана из файла конфига.
* На вход принимает только ВАЛИДНУЮ строку.
* Разрешение экрана строка типа: R 1920 1080
*/

int			res_handler(char *line, m_resolution **res)
{
	size_t	i;
	size_t	flag_x;
	char	*tmp;

	i = 1;
	flag_x = 0;
	tmp = line;
	while (line[i])
	{
		if (line[i] == ' ' || (ft_isdigit(line[i]) && ft_isdigit(line[i - 1])))
			i++;
		if (ft_isdigit(line[i]) && !ft_isdigit(line[i - 1]))
		{
			if (flag_x == 0)
			{
				(*res)->x = ft_atoi(tmp + i);
				flag_x = 1;
			}
			else
				(*res)->y = ft_atoi(tmp + i);
			i++;
		}
	}
	return (0);
}

/*
* Предполагается что функция будет обрабатывать строку из файла и для каждой опции вызывать нужный суб-обработчик
*/
int			line_handler(char *line)
{
	while (line)
	{
		if (*line == 'R')
			res_handler(line);
		if (*line = 'N' || *line == 'S' \
			|| *line == 'W' || *line == 'E' || *line == 'S')
			texture_handler(line);
		if (*line == 'F' || *line == 'C')
			color_handler(line);
		if (*line == 1)
			map_handler(line);
		
	}
}

/*
* Должен сохранять ТОЛЬКО карту в двумерный массив.
* Пока непонятно как считать длину самой длинной строчки в карте, чтобы по ней выделять память.
*/
// void		make_map(t_list **head, int size) 
// {
// 	char	**map;
// 	t_list	*tmp;
// 	int		i;

// 	i = -1;
// 	if(!(map = (char **)ft_calloc(size + 1, sizeof(char *))))
// 		return ;
// 	tmp = *head;
// 	while (tmp)
// 	{
// 			map[++i] = tmp->content; // надо выделять память под каждую строку?
// 			tmp = tmp->next;
// 	}
// }

int				main (int argc, char * argv[])
{
	int			fd;
	char		*line;
	t_list		*head;
	m_config	*config;

	line = NULL;
	head = NULL;
	config = NULL;

	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line)) // malloc line
	{
		if (line_handler(line &config))
			if (!(ft_lstadd_back(&head, ft_lstnew(line)))) //malloc ft_lstnew
				return (ERROR);
		else
			return (ERROR);
	}
	if (!(ft_lstadd_back(&head, ft_lstnew(line)))) //malloc ft_lstnew
			return (ERROR);
	make_map(&head, ft_lstsize(head));
	return (OK);
}
