/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:47:59 by amayor            #+#    #+#             */
/*   Updated: 2020/11/01 20:48:08 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

int	move_f(int keycode, t_world **world)
{
	if (keycode == 65362)
	{
		(*world)->plr->y -= 10;
		draw_flat_map(*world);
	}
	return (0);
}