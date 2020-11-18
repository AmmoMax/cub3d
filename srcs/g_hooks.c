/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:47:59 by amayor            #+#    #+#             */
/*   Updated: 2020/11/18 21:58:11 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void	move_forward_back(t_world **world, int keycode)
{
	float	y;
	float	x;

	if (keycode == 119)
	{
		x = (*world)->plr->x + cos((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y - sin((*world)->plr->dir) * SPEED;
	}
	else
	{
		x = (*world)->plr->x - cos((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y + sin((*world)->plr->dir) * SPEED;
	}
	
	check_location(world, x, y);
	draw_3d_map(*world , 0);
	mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
}

static void	turn_left_right(t_world **world, int keycode)
{
	if (keycode == 65361)
	{
		(*world)->plr->dir += 0.02;
		if ((*world)->plr->dir > 2 * M_PI)
			(*world)->plr->dir -= 2 * M_PI;
		else if ((*world)->plr->dir < 0)
			(*world)->plr->dir += 2 * M_PI;
	}
	else
	{
		(*world)->plr->dir -= 0.02;
		if ((*world)->plr->dir > 2 * M_PI)
			(*world)->plr->dir -= 2 * M_PI;
		else if ((*world)->plr->dir < 0)
			(*world)->plr->dir += 2 * M_PI;
	}
	draw_3d_map(*world, 0);
	mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
}

static void	move_left_right(t_world **world, int keycode)
{
	float	y;
	float	x;

	if (keycode == 97)
	{
		x = (*world)->plr->x - sin((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y - cos((*world)->plr->dir) * SPEED;
	}
	else
	{
		x = (*world)->plr->x + sin((*world)->plr->dir) * SPEED;
		y = (*world)->plr->y + cos((*world)->plr->dir) * SPEED;
	}
	check_location(world, x, y);
	draw_3d_map(*world, 0);
	mlx_put_image_to_window((*world)->win->mlx, (*world)->win->win, (*world)->win->img, START_X, START_Y);
}

int			move_handler(int keycode, t_world **world)
{
	if (keycode == 119 || keycode == 115)
		move_forward_back(world, keycode);
	else if (keycode == 65361 || keycode == 65363)
		turn_left_right(world, keycode);
	else if (keycode == 97 || keycode == 100)
		move_left_right(world, keycode);
	return (0);
}
