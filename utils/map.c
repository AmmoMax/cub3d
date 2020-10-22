#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "libft.h"
#include <fcntl.h>

char				*ft_strcpy(char *dst, const char *src)
{
	size_t			i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

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
* Возвращает символ-сосед, который находится над текущим символом.
* Принимает указатель на текущий символ
*
*/
char	get_up_neighbour(char *str, int max_len)
{
	char *tmp;

	tmp = str - max_len;
	printf("neighbour for [%c] is [%c]\n", *str, *tmp);
	return (*tmp);
}

/*
* Нормализует карту, дополняя кажду строку пробелами до длины самой длинной строки.
* Принимает указатель на карту и максимальную длину строки в карте.
*
*/
void		normalize_map(char **map, int max_len)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	while(map[i] != 0)
	{
		str_len = ft_strlen(map[i]);
		if (str_len < max_len)
		{
			while (str_len < max_len)
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
	size_t	i;

	i = 1;
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


/*
*
* ФУНКЦИЯ ТЕСТОВАЯ, НЕ ИСПОЛЬЗОВАТЬ НА ПРОДЕ.
*/
void	print_map(char **map)
{
	size_t	i;

	printf("*** Start print_map ***\n");
	i = 0;
	while (map[i])
	{
		printf("%ld :: *%s*\n", i, map[i]);
		i++;
	}
	printf("*** End print_map ***\n");
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
static int map_validator_old(char *line, m_config **config)
{
	
	if (!((*config)->map)) // если это первая строка
		return (first_line_map_v(line));
	else
		return (common_line_map_v(line));
	
}

/*
* Добавляет в конец односвязного списка, который представляет карту, новую строку.
* Принимает строку и общий конфиг.
* TODO: Добавить проверку выделения памяти под структуру и очистку
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
int map_handler_old(char *line, m_config **config, int flag_last_line)
{
	if (flag_last_line == 0)
	{
		if (map_validator_old(line, config) == 0)
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

/*
* Общий обработчик строки карты. В зависимости строки вызывает нужный валидатор.
* Принимает указатель на строку и флаг линии - по нему опрделяется первая строка,
* последняя и все остальные.
* Возвращает код: 1 - ошибка, 0 - ОК
*/
int	map_handler(char *line, m_config **config)
{
	return (map_parser(line, config));
}

/*
* Валидирует карту из двумерного массива.
* Вызывает три отдельных валидатор - для первой строки, для последней
* и всех остальных.
* Принимает указатель на карту и длину карты.
* Возвращает 1 если карта не валидна и 0 если валидна
*/
int	map_validator(char **map, int len_map)
{
	size_t	i;
	int		len_str;

	i = -1;
	while (map[++i])
	{
		len_str = ft_strlen(map[i]);
		if (i == 0)
			if (!(validator_1_str(map[i]) == 0))
				return (1);
		else if (i == (len_map - 1))
			if (!(validator_last_str(map[i]) == 0))
				return (1);
		else
			if (!(validator_common_str(map[i], len_str) == 0))
				return (1);
	}
	return (0);
}

/*
* Валидирует первую строку карты.
* Первая строка может состоять из любого количество 1 и пробелов
* Принимает указатель на строку.
* Возвращает 0 если строка валидна и 1 если нет.
*/
static int	validator_1_str(char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == 1 || str[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

/*
* Валидирует последнюю строку карты.
* Последняя строка как и первая может состоять только из пробелов и 1, т.к.
* если предыдущая строка валидна то все дырки закрыты единицами.
*/
static int	validator_last_str(char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == 1 || str[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

/*
* Валирует обычную строку карты.
* 
* TODO: Добавить проверку на наличие в карте > 1 игрока.
*/
static int	validator_common_str(char *str, int len)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		
	}

}

int main()
{
	char 		*map_line;
	int			fd;
	m_config	config;
	m_config	*config_p;
	char 		**map;
	size_t		i = 0;
	char		str;
	int			len_map;

	config_p = &config;
	config.map = NULL;
	fd = open("map.cub", O_RDONLY);
	while (get_next_line(fd, &map_line))
	{
		// printf("map_line = %s\n", map_line);
		// map_parser(map_line, &config_p);
		map_handler(map_line, &config_p);
	}
	// printf("last line = %s\n", map_line);
	map_handler(map_line, &config_p);
	close(fd);
	map = convert_map(config.map);
	print_map(map);
	len_map = ft_lstsize(config.map);
	if (map_validator(map, len_map))
		printf("Map is NOT VALID!");
	else
		printf("Map is VALID!");
		

	// TODO: написать функцию очистки памяти под список с картой

	// str = get_up_neighbour(&map[0][28], max_len_line(config.map));
	return (0);
}