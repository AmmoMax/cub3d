/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_3d_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:53:16 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 14:55:14 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

void	draw_3d_map(t_world *world, int save_flag)
{
	cast_rays_dda(world);
	sprite_finder(world);
	if (save_flag)
		make_screen(world);
	mlx_do_sync(world->win->mlx);
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}
