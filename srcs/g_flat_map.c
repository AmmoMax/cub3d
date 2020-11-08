/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flat_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:24:26 by amayor            #+#    #+#             */
/*   Updated: 2020/11/07 22:47:54 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

void		draw_block(t_win *win, int color, int x, int y)
{
	int			i;
	int			j;

	i = y;
	while (i <  (y + SCALE))
	{
		j = x;
		while (j < (x + SCALE))
		{
			my_mlx_pixel_put(win, j, i, color);
			j++;;
		}
		i++;
	}
}

void		draw_player(t_win *win, int color, int x, int y)
{
	my_mlx_pixel_put(win, x, y, color);
}

void		draw_column(t_world *world, float x, float height, int color)
{
	float y_start;
	float y;

	if (height > world->config->y)
		height = world->config->y;
	y_start = world->config->y / 2 - height / 2;
	// y = y_start;
	y = 0;
	while (y < y_start)
	{
		my_mlx_pixel_put(world->win, x, y, 0xFFD700);
		y++;
	}
	while (height > 0)
	{
		my_mlx_pixel_put(world->win, x, y, color);
		y++;
		height--;
	}
	while (y < world->config->y)
	{
		my_mlx_pixel_put(world->win, x, y, 0x808080);
		y++;
	}
}

int			check_plr_pos(t_world *world, int x, int y)
{
	if ((x == (int)world->plr->x) && y == (int)world->plr->y)
		return (1);
	else if (((int)world->plr->y > y) && ((int)world->plr->y < (y + SCALE)) && (int)world->plr->x == x)
		return (1);
	else
		return (0);
}

void			draw_flat_map(t_world *world)
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	**map;
	
	i = 0;
	x = START_X;
	y = START_Y;
	map = world->map;
	
	while (map[i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1' || map[i][j] == '2')
			{
				draw_block(world->win, CLR_BLK, x, y);
				x += SCALE;
			}
			else
			{
				draw_block(world->win, 0x000000, x, y);
				x += SCALE;
			}
		}
		y += SCALE;
		x = 100;
		i++;
	}
	draw_player(world->win, CLR_PLR, world->plr->x, world->plr->y);
	cast_rays_flat(world);
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}

void	draw_3d_map(t_world *world)
{
	// cast_rays(world);
	cast_rays_dda(world);
	// mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}