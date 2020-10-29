/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:49:02 by amayor            #+#    #+#             */
/*   Updated: 2020/10/29 23:12:43 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

#include <stdio.h>
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

int				start_cub3d(char *path, char *save_flag)
{
	m_config	*config;
	int			len_map;
	// t_world		*world;

	if (save_flag && ft_strncmp("--save", save_flag, ft_strlen(save_flag)) == 1)
		return (1); // TODO: обработка ошибки - параметр не равен --save
	ft_putstr_fd("Start reading map file...\n", 1);
	if (!(config = read_config(path)))
		return (1); // TODO: ошибка при чтении или парсинге карты(?)
	config->flat_map = convert_map(config->map);
	if (!(config->flat_map))
		return (ERR_MEMALLOC);
	len_map = ft_lstsize(config->map);
	if (map_validator(config->flat_map, len_map) != 0)
		return (ERR_INVMAP);
	print_map(config->flat_map);
	return (0);
}