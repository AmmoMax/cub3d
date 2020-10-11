#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "libft.h"
#include <fcntl.h>

/*
* Валидирует конкретную строку карты.
* Валидная строка начинается и заканчивается 1.
* Если это первая строка карты - она вся содержит 1.
* Если это последняя строка карты - она вся содержит 1 и EOF.
*/
static int map_validator()
{

}

static int map_parser()
{

}

/*
* Обработчик строки предполагаемой карты из файла.
* В аргументах получает строку с картой и общий конфиг.
*/
int map_handler(char *line, m_config **config)
{
	if (map_validator(line) == 0)
		return (map_parser);
}


int main()
{
	char 		*map_line;
	int			fd;
	m_config	config;
	size_t		i;

	i = 0;
	fd = open('map.cub', O_RDONLY);
	while (get_next_line(fd, map_line))
	{
		if(map_handler)
		{
			printf("Map is INVALID!\n");
			return (1);
		}
		printf("Map line is valid!\n");
		printf("line map: %s\n", config.map[i]);
		i++;
	}
	return (0);
}