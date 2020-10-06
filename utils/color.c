#include "utils.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!str[i])
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || \
			str[i] == '\f' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * sign);
}

/*
*
* Валидирует строку с кодом цвета в RGB
* Пример валидной строки: "F 220,100,0";
* Валидная строка:
*	Содержит любое количество пробелов между элементами
*	Начинается с буквы F или C
*	Содержит ровно 3 числа от 0 до 255
*
* TODO: Добавить обработку переполнения atoi
*/
static int	color_validator(char *line)
{
	size_t	i;
	size_t	num_cnt;
	char 	*tmp;
	size_t	flag_color;

	i = -1;
	num_cnt = 0;
	tmp = line;
	// flag_color = 0;
	while(line[++i])
	{
		if ((line[i] == 'C' || line[i] == 'F') && line[i + 1] == ' ')
				flag_color = 1;
		else if (line[i] == ' ' || line[i] == ',' ||
				(ft_isdigit(line[i]) && ft_isdigit(line[i - 1])))
				;
		else if (ft_isdigit(line[i]) && !(ft_isdigit(line[i - 1])))
		{
			if (ft_atoi(tmp + i) > 255 || ft_atoi(tmp + i) < 0 || flag_color != 1)
				return (1);
			num_cnt++;
		}
		else
			return (1);
	}
	return (num_cnt == 3 ? 0 : 1);
}

static int	color_parser(char *line, m_config **m_config)
{
	return (0);
}

int	color_handler(char *line, m_config **config)
{
	color		floor;
	color		*floor_p;
	color		ceiling;
	color		*ceiling_p;

	if (color_validator(line) == 0)
		return(color_parser(line, config));
	else
		return (1);


}


int main()
{
	char		*valid;
	char		*invalid;
	m_config	config;
	m_config	*config_p;

	config_p = &config;
	valid = "C 100,255,255";
	invalid = "F 122,31 ";
	if (color_handler(valid, &config_p) == 0)
	{
		printf("Color param is valid!\n");
		// printf("Color param = %s");
	}
	else
	{
		printf("Color param is INvalid!\n");
	}

	// printf("Ceiling color. Red: %d, Green: %d, Blue: %d", config.ceiling->red, config.ceiling->green, config.ceiling->blue);
	return (0);
}