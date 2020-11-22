/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:09:13 by amayor            #+#    #+#             */
/*   Updated: 2020/11/22 21:27:27 by amayor           ###   ########.fr       */
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
		{
			print_err(ERR_MAP_SURWALLS);
			return (ERR_MAP_SURWALLS);
		}
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
		{
			print_err(ERR_MAP_SURWALLS);
			return (ERR_MAP_SURWALLS);
		}
	}
	return (0);
}

static int	print_error(int err)
{
	print_err(err);
	return (err);
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
		return (print_error(ERR_MAP_SURWALLS));
	else if (*(str - (len + 1)) == ' ')
		return (print_error(ERR_MAP_SURWALLS));
	else if (*(str - (len + 2)) == ' ')
		return (print_error(ERR_MAP_SURWALLS));
	else if (*(str - 1) == ' ')
		return (print_error(ERR_MAP_SURWALLS));
	else if ((*(str + 1) == ' ') || (*(str + 1) == '\0'))
		return (print_error(ERR_MAP_SURWALLS));
	else if (*(str + len) == ' ')
		return (print_error(ERR_MAP_SURWALLS));
	else if (*(str + (len + 1)) == 32)
		return (print_error(ERR_MAP_SURWALLS));
	else if (*(str + (len + 2)) == ' ')
		return (print_error(ERR_MAP_SURWALLS));
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

	i = 0;
	if (str[0] == ' ' || str[0] == '1')
		while (str[++i])
			if ((str[i] == ' ' || str[i] == '1' || str[i] == '2') ||
					(str[i] == '0' && check_zero_symbol(str + i, len) == 0))
				;
			else if ((str[i] == 'N' || str[i] == 'S' || 
					 str[i] == 'W' || str[i] == 'E') && 
					 check_zero_symbol(str + i, len) == 0)
					(*flag_gamer)++;
			else
				return(print_error(ERR_INVMAP));
	else
		return (print_error(ERR_MAP_SURWALLS));
	return (0);
}

/*
* Валидирует карту из двумерного массива.
* Вызывает три отдельных валидатора - для первой строки, для последней
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
	return (check_player(flag_gamer));
	// return (flag_gamer == 1 ? 0 : ERR_MAP_NOGMR_POS);
}

int	check_player(int flag)
{
	if (flag > 1)
	{
		print_err(ERR_DOUBLE_PLR);
		return (1);
	}
	else if (flag < 1)
	{
		print_err(ERR_MAP_NOGMR_POS);
		return (1);
	}
	else
		return (0);
}