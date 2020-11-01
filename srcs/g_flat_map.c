/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flat_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:24:26 by amayor            #+#    #+#             */
/*   Updated: 2020/11/01 21:01:40 by amayor           ###   ########.fr       */
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

int				draw_flat_map_old(t_world **p_world)
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

void		print_maps_block(t_world *world, int x, int y)
{
	draw_block(world->win, SCALE, CLR_BLK);
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, x, y);
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

void		print_plr_block(t_world *world, int x, int y)
{
	draw_block(world->win, SCALE, CLR_PLR);
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, x, y);
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
				print_maps_block(world, x ,y);
				// draw_block(world->win, SCALE, CLR_BLK);
				x += SCALE;
			}
			else if (check_plr_pos(world, x , y))
			{
				// print_plr_block(world, world->plr->x, world->plr->y);
				print_plr_block(world, x, y);
				// draw_block(world->win, SCALE, CLR_PLR);
				x += SCALE;
			}
			else
				x += SCALE;
		}
		y += SCALE;
		x = 100;
		i++;
	}
	// print_plr_block(world, world->plr->x, world->plr->y);
	// mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);

}
