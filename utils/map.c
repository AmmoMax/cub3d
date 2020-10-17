#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "libft.h"
#include <fcntl.h>

static int	first_line_map_v(char *line)
{
	size_t	i;
	size_t	num_flag;

	i = 0;
	num_flag = 0;
	while (line[i])
	{
		if (line[i] == ' ' && num_flag == 0)
			i++;
		else if (line[i] == '1')
		{
			num_flag = 1;
			i++;
		}
		else
			return (1);
	}
	return (0);
}


int	max_len_line(t_list *head)
{
	int max_len;
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
* Конвертирует карту из формата односвязного списка в двумерный массив.
* Принимает указатель на первый элемент списка.
* Возвращает указатель на двумерный массив.
*/
char		**convert_map(t_list *head)
{
	int		max_len;
	char 	**map;
	size_t	i;

	i = 0;
	max_len = max_len_line(head);
	map = (char **)ft_calloc(ft_lstsize(head) + 1, sizeof(char *));
	while (head->next)
	{
		map[i] = head->content;
		i++;
		head = head->next;
	}
	map[i] = head->content;
	return (map);
}

void	print_map(char **map)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (map[++i])
	{
		printf("%ld :: %s\n", i, map[i]);
	}
	
}

static int	common_line_map_v(char *line)
{
	size_t	i;
	t_list	*map;

	if (line[0] != '1')
		return (1);
	i = 1;
	while(line[i])
	{
		if (line[i] == '1' || line[i] == '0' || 
			line[i] == '2' || line[i] == 'N' || 
			line[i] == 'S' || line[i] == 'W' || 
			line[i] == 'E' || (line[i] == '1' && line[i + 1] == '\0'))
			i++;
		else
			return (1);
	}
	return (0);
}

/*
* Валидирует конкретную строку карты.
* Валидная строка начинается и заканчивается 1.
* Если это первая строка карты - она вся содержит 1.
* Если это последняя строка карты - она вся содержит 1 и EOF.
*/
static int map_validator(char *line, m_config **config)
{
	
	if (!((*config)->map)) // если это первая строка
		return (first_line_map_v(line));
	else
		return (common_line_map_v(line));
	
}

/*
* Добавляет в конец односвязного списка, который представляет карту, новую строку.
* Принимает строку и общий конфиг.
*
*/
static int map_parser(char *line, m_config **config)
{
	t_list	*map_string;
	t_list	**map;

	map = &(*config)->map;
	map_string = ft_lstnew(line);

	return (ft_lstadd_back(map, map_string));
}

/*
* Обработчик строки предполагаемой карты из файла.
* Принимает строку с картой и общий конфиг.
*/
int map_handler(char *line, m_config **config, int flag_last_line)
{
	if (flag_last_line == 0)
	{
		if (map_validator(line, config) == 0)
			return (map_parser(line, config));
		else
			return (1);
	}
	else
		if (first_line_map_v(line) == 0)
			return (map_parser(line, config));
		else
			return (1);
}

int main()
{
	char 		*map_line;
	int			fd;
	m_config	config;
	m_config	*config_p;

	config_p = &config;
	config.map = NULL;
	fd = open("map.cub", O_RDONLY);
	while (get_next_line(fd, &map_line))
	{
		printf("map_line = %s\n", map_line);
		if(map_handler(map_line, &config_p, 0) == 0)
		{
			printf("Line is valid!\n");
		}
		else
		{
			printf("Line is INVALID!\n");
			return (1);
		}
	}
	printf("last line = %s\n", map_line);
	if (map_handler(map_line, &config_p, 1) == 1)
	{
		printf("Map is INVALID!\n");
		return (1);
	}
	close(fd);
	printf("Map is valid!\n\n");
	printf("max len in map: %d\n", max_len_line(config.map));
	print_map(convert_map(config.map));
	return (0);
}