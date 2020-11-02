/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flat_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:24:26 by amayor            #+#    #+#             */
/*   Updated: 2020/11/02 11:52:49 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void		draw_block(t_win *win, int color, int x, int y)
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
			j ++;;
		}
		i ++;
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
			else if (check_plr_pos(world, x , y))
			{
				draw_block(world->win, CLR_PLR, x, y);
				x += SCALE;
			}
			else
				x += SCALE;
		}
		y += SCALE;
		x = 100;
		i++;
	}
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}