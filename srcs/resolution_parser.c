/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:28:35 by amayor            #+#    #+#             */
/*   Updated: 2020/09/12 22:39:14 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"


/*
*Принимает необработанную строку от парсера файла конфигурации.
Валидирует и парсит строку, сохраняет разрешение в общую структуру.
Если строка невалидна - возвращает ошибку.
TODO: Добавить конкретный код ошибки о невалидной строке. 
*/

void		res_handler(char *line, m_resolution **res)
{
	if (res_validator == 0)
		res_parser(line, res);
	else
		return 1;
}

/*
* Парсинг строки с разрешением экрана из файла конфига.
* На вход принимает только ВАЛИДНУЮ строку.
* Разрешение экрана строка типа: R 1920 1080
*/
void			res_parser(char *line, m_resolution **res)
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
