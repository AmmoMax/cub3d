/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:47:59 by amayor            #+#    #+#             */
/*   Updated: 2020/11/08 19:00:36 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

int			move_f(int keycode, t_world **world)
{
	float	y;
	float	x;

	if (keycode == 65362)
	{
		x = (*world)->plr->x + cos((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y + sin((*world)->plr->dir) * SPEED;
		draw_player((*world)->win, 0x000000, (*world)->plr->x, (*world)->plr->y);
		check_location(world, x, y);
		draw_flat_map(*world);
		draw_player((*world)->win, CLR_PLR, (*world)->plr->x, (*world)->plr->y);
		mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
	}
	else if (keycode == 65364)
	{
		x = (*world)->plr->x - cos((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y - sin((*world)->plr->dir) * SPEED;
		draw_player((*world)->win, 0x000000, (*world)->plr->x, (*world)->plr->y);
		check_location(world, x, y);
		draw_flat_map(*world);
		draw_player((*world)->win, CLR_PLR, (*world)->plr->x, (*world)->plr->y);
		mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
	}
	else if (keycode == 65361)
	{
		(*world)->plr->dir -= M_PI / 90;
		draw_flat_map(*world);
	}
	else if (keycode == 65363)
	{
		(*world)->plr->dir += M_PI / 90;
		draw_flat_map(*world);
	}
	return (0);
}

int			move_forward(int keycode, t_world **world)
{
	float	y;
	float	x;

	if (keycode == 65362)
	{
		mlx_clear_window((*world)->win->mlx, (*world)->win->win);
		x = (*world)->plr->x + cos((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y - sin((*world)->plr->dir) * SPEED;
		check_location(world, x, y);
		draw_3d_map(*world);
		mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
	}
	else if (keycode == 65364)
	{
		mlx_clear_window((*world)->win->mlx, (*world)->win->win);
		x = (*world)->plr->x - cos((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y + sin((*world)->plr->dir) * SPEED;
		check_location(world, x, y);
		draw_3d_map(*world);
		mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
	}
	else if (keycode == 65361)
	{
		(*world)->plr->dir += M_PI / 90;
		// (*world)->plr->dir += 0.02;
		if ((*world)->plr->dir > 2 * M_PI)
			(*world)->plr->dir -= 2 * M_PI;
		else if ((*world)->plr->dir < 0)
			(*world)->plr->dir += 2 * M_PI;
		printf("DIR = %f degrees\n", ((*world)->plr->dir * 180) / M_PI);
		draw_3d_map(*world);
	}
	else if (keycode == 65363)
	{
		(*world)->plr->dir -= M_PI / 90;
		// (*world)->plr->dir -= 0.02;
		if ((*world)->plr->dir > 2 * M_PI)
			(*world)->plr->dir -= 2 * M_PI;
		else if ((*world)->plr->dir < 0)
			(*world)->plr->dir += 2 * M_PI;
		printf("DIR = %f degrees\n", ((*world)->plr->dir * 180) / M_PI);
		draw_3d_map(*world);
	}
	return (0);
}
