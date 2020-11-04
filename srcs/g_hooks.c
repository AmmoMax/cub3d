/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:47:59 by amayor            #+#    #+#             */
/*   Updated: 2020/11/03 21:40:24 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

int			move_f(int keycode, t_world **world)
{
	float	y;
	float	x;

	if (keycode == 65362)
	{
		// y = (*world)->plr->y - SPEED;
		x = (*world)->plr->x + cos((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y + sin((*world)->plr->dir) * SPEED;
		draw_player((*world)->win, 0x000000, (*world)->plr->x, (*world)->plr->y);
		check_location(world, x, y);
		// (*world)->plr->y -= 10;
		draw_flat_map(*world);
		draw_player((*world)->win, CLR_PLR, (*world)->plr->x, (*world)->plr->y);
		mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
	}
	else if (keycode == 65364)
	{
		// y = (*world)->plr->y + SPEED;
		x = (*world)->plr->x - cos((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y - sin((*world)->plr->dir) * SPEED;
		draw_player((*world)->win, 0x000000, (*world)->plr->x, (*world)->plr->y);
		check_location(world, x, y);
		// (*world)->plr->y += 10;
		draw_flat_map(*world);
		draw_player((*world)->win, CLR_PLR, (*world)->plr->x, (*world)->plr->y);
		mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
	}
	else if (keycode == 65361)
	{
		(*world)->plr->dir += 0.2;
		draw_flat_map(*world);
	}
	else if (keycode == 65363)
	{
		(*world)->plr->dir -= 0.2;
		draw_flat_map(*world);
	}
	// {
	// 	x = (*world)->plr->x - SPEED;
	// 	draw_player((*world)->win, 0x000000, (*world)->plr->x, (*world)->plr->y);
	// 	check_location(world, x, (*world)->plr->y);
	// 	// (*world)->plr->x -= 10;
	// 	draw_flat_map(*world);
	// 	draw_player((*world)->win, CLR_PLR, (*world)->plr->x, (*world)->plr->y);
	// 	mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
	// }
	// else if (keycode == 65363)
	// {
	// 	x = (*world)->plr->x + SPEED;
	// 	draw_player((*world)->win, 0x000000, (*world)->plr->x, (*world)->plr->y);
	// 	check_location(world, x, (*world)->plr->y);
	// 	// (*world)->plr->x += 10;
	// 	draw_flat_map(*world);
	// 	draw_player((*world)->win, CLR_PLR, (*world)->plr->x, (*world)->plr->y);
	// 	mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
	// }
	return (0);
}
