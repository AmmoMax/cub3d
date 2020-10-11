#include <stdlib.h>
#include <stdio.h>
#include "utils.h"


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
	if
}