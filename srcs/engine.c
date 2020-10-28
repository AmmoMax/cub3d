/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:49:02 by amayor            #+#    #+#             */
/*   Updated: 2020/10/28 12:32:23 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

int				start_cub_3d(char *path, char *save_flag)
{
	m_config	*config;
	t_world		*world;

	if (save_flag && ft_strncmp("--save", save_flag, ft_strlen(save_flag)) == 1)
		return (1); // TODO: обработка ошибки - параметр не равен --save
	ft_putstr_fd("Start reading map file...", 1);
	if (!(config = read_config(path)))
		return (1); // TODO: ошибка при чтении или парсинге карты(?)
		
}