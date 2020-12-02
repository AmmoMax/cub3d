/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:09:13 by amayor            #+#    #+#             */
/*   Updated: 2020/11/28 20:01:51 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Валидирует первую строку карты.
*/

static int	validator_1_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
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
** Валидирует последнюю строку карты.
*/

static int	validator_last_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
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
** Проверяет клетку с пустым пространством в карте, т.е. с 0.
** Проверяет чтобы клетка с нулем была закрытой - т.е. не соседствовала
** с пробелом ни по одному из 8 направлений
*/

static int	check_zero_symbol(char *str, int len)
{
	if (*(str - len) == ' ')
		return (local_print_error(ERR_MAP_SURWALLS));
	else if (*(str - (len + 1)) == ' ')
		return (local_print_error(ERR_MAP_SURWALLS));
	else if (*(str - (len + 2)) == ' ')
		return (local_print_error(ERR_MAP_SURWALLS));
	else if (*(str - 1) == ' ')
		return (local_print_error(ERR_MAP_SURWALLS));
	else if ((*(str + 1) == ' ') || (*(str + 1) == '\0'))
		return (local_print_error(ERR_MAP_SURWALLS));
	else if (*(str + len) == ' ')
		return (local_print_error(ERR_MAP_SURWALLS));
	else if (*(str + (len + 1)) == 32)
		return (local_print_error(ERR_MAP_SURWALLS));
	else if (*(str + (len + 2)) == ' ')
		return (local_print_error(ERR_MAP_SURWALLS));
	else
		return (0);
}

/*
** Валирует обычную строку карты относительно других строк.
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
				return (local_print_error(ERR_INVMAP));
	else
		return (local_print_error(ERR_MAP_SURWALLS));
	return (0);
}

/*
** Валидирует карту из двумерного массива.
** Вызывает три отдельных валидатора - для первой строки,
** для последней и всех остальных.
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
			{
				if (!(validator_common_str(map[i], len_str, &flag_gamer) == 0))
					return (ERR_INVMAP);
			}
		}
	return (check_player(flag_gamer));
}
