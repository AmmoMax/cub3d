/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:09:13 by amayor            #+#    #+#             */
/*   Updated: 2020/10/31 15:05:06 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

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
	while (str[i])
	{
		if (str[i] == '1' || str[i] == ' ')
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
	while (str[i])
	{
		if (str[i] == '1' || str[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

/*
* Проверяет клетку с пустым пространством в карте, т.е. с 0.
* Проверяет чтобы клетка с нулем была закрытой - т.е. не соседствовала
* с пробелом ни по одному из 8 направлений
* Если клетка валидна - возвращает 0, если нет то 1.
*/
static int	check_zero_symbol(char *str, int len)
{
	if (*(str - len) == ' ')
		return (1);
	else if (*(str - (len + 1)) == ' ')
		return (1);
	else if (*(str - (len + 2)) == ' ')
		return (1);
	else if (*(str - 1) == ' ')
		return (1);
	else if ((*(str + 1) == ' ') || (*(str + 1) == '\0'))
		return (1);
	else if (*(str + len) == ' ')
		return (1);
	else if (*(str + (len + 1)) == 32)
		return (1);
	else if (*(str + (len + 2)) == ' ')
		return (1);
	else
		return (0);
}

/*
* Валирует обычную строку карты относительно других строк.
* Принимает указатель на текущую строку карты и длину этой строки
*/
static int	validator_common_str(char *str, int len, int *flag_gamer)
{
	size_t	i;

	i = 1;
	if (str[0] == ' ' || str[0] == '1')
		while (str[i])
		{
			if (str[i] == ' ' || str[i] == '1' || str[i] == '2')
				i++;
			else if (str[i] == '0' && check_zero_symbol(str + i, len) == 0)
				i++;
			else if ((str[i] == 'N' || str[i] == 'S' || 
					 str[i] == 'W' || str[i] == 'E') && 
					 check_zero_symbol(str + i, len) == 0)
				{
					i++;
					(*flag_gamer)++;
				}
			else
				return (1);
		}
	else
		return (1);
	return (0);
}

/*
* Валидирует карту из двумерного массива.
* Вызывает три отдельных валидатор - для первой строки, для последней
* и всех остальных.
* Принимает указатель на карту и длину карты.
* Возвращает ERR_INVMAP если карта не валидна и 0 если валидна
*/
int			map_validator(char **map, int len_map)
{
	int		i;
	int		len_str;
	int		flag_gamer;

	i = 0;
	flag_gamer = 0;
	if (!(validator_1_str(map[i]) == 0))
		return (1);
	else
		while (map[++i])
		{
			len_str = ft_strlen(map[i]);
			if (i == (len_map - 1))
			{
				if (!(validator_last_str(map[i]) == 0))
					return (ERR_INVMAP);
			}
			else
				if (!(validator_common_str(map[i], len_str, &flag_gamer) == 0))
					return (ERR_INVMAP);
		}
	return (flag_gamer == 1 ? 0 : ERR_INVMAP);
}