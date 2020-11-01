/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flat_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:24:26 by amayor            #+#    #+#             */
/*   Updated: 2020/11/01 14:31:33 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void		draw_block(t_win *win, int side, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < side)
	{
		j = 0;
		while (j < side)
		{
			my_mlx_pixel_put(win, i, j, color);
			j++;
		}
		i++;
	}
}

int	draw_flat_map(t_world **p_world)
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	**map;
	t_world *world;
	
	i = 0;
	x = 100;
	y = 100;
	world = *p_world;
	map = world->map;
	
	while (map[i])
	{
		j = -1;
		while(map[i][++j])
		{
			if(map[i][j] == '1' || map[i][j] == '2')
			{
				draw_block(world->win, SCALE, 0xFF1497);
				mlx_put_image_to_window(world->win->mlx, 
						world->win->win, world->win->img, x, y);
				x += SCALE;
			}
			else if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S')
			{
				world->plr->x = x;
				world->plr->y = y;
				draw_block(world->win, SCALE, 0x00FFFF);
				mlx_put_image_to_window(world->win->mlx, 
						world->win->win, world->win->img, x, y);
				x += SCALE;
			}
			else
				x += SCALE;
		}
		y += SCALE;
		x = 100;
		i++;
	}
	return (0);
}
