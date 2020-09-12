/*
* Выделяет из строки с разрешением числа разрешения
Пример входной строки: R 1920 1080
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct			resolution
{
	int					x;
	int					y;
}						m_resolution;

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


void			res_handler(char *line, m_resolution **res)
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
}

/*
* Валидирует строку.
* Валидная строка: начинается с R, потом идет любое количество пробелов и два числа > 0, разделенные любым кол-вом пробелов.
* Возвращает 0 если строка валидна, и 1 если невалидна.
* Строка невалидна если:
* 1. Если в строке есть буквы кроме R
* 2. Если перед R есть числа
* 3. Если одно из чисел разрешения содержит в себе букву
* 4. Если чисел разрешения больше чем 2.
* 5. 
* "R  1920   1080";v
* "1  R  1920   1080";iv
* "R  19a20   1080";iv
* "q  19a20   1080";iv
*/
int				res_validator(char *line)
{
	size_t		i;
	size_t		nbr_count;
	int			flag_r;

	i = 0;
	nbr_count = 0;
	flag_r = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == 'R' && line[i + 1] == ' ' && flag_r == 0)
		{
			i++;
			flag_r = 1;
		}
		else if (ft_isdigit(line[i]) && line[i + 1] == ' ' && flag_r == 1 && nbr_count < 2)
		{
			nbr_count++;
			i++;
		}
		else if (ft_isdigit(line[i]) && (ft_isdigit(line[i + 1]) || line[i + 1] == '\0'))
			i++;
		else
			return (1);
	}
	return (0);
}

int main()
{
	char			*line;
	// m_resolution	*res;


	line = "R   1920  1080";
	// res->x = 0;	
	// res->y = 0;
	if (res_validator(line) == 1)
		printf("Map is invalid\n\n");
	else
		printf("Map is valid\n\n");
	// res_handler(line, &res);
	// printf("x = %d\ny = %d\n", res->x ,res->y);
}