/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:24:53 by amayor            #+#    #+#             */
/*   Updated: 2020/10/28 11:46:39 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"


int	main(int argc, char **argv)
{
	char	*cub_path;
	char	*save_flag;

	cub_path = NULL;
	save_flag = NULL;
	if (argc == 2 || argc == 3)
	{
		cub_path = argv[1];
		if (argc == 3)
			save_flag = argv[2];
		if (start_cub3d(cub_path, save_flag))
			return (1); // TODO: добавить обработку ошибки которая возвращается из самого куба
	}
	else if (argc == 1)
		return (1); // TODO: добавить обработку ошибки отсутствия карты
	else
		return (1); // TODO: добавить ошибку - слишком много аргументов
}