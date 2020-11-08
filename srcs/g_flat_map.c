/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flat_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:24:26 by amayor            #+#    #+#             */
/*   Updated: 2020/11/08 22:02:09 by amayor           ###   ########.fr       */
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

static int get_wall_c(char c_wall)
{
	if (c_wall == 'N')
		return (0x00FFFF);
	if (c_wall == 'S')
		return (0xFFD700);
	if (c_wall == 'E')
		return (0xFF4500);
	if (c_wall == 'W')
		return (0x8A2BE2);
	return (0);
}

void		draw_column(t_world *world, float x, float height, char c_wall)
{
	float y_start;
	float y;

	if (height > world->config->y)
		height = world->config->y;
	y_start = world->config->y / 2 - height / 2;
	y = 0;
	while (y < y_start)
	{
		my_mlx_pixel_put(world->win, x, y, 0xFFFFFF);
		y++;
	}
	while (height > 0)
	{
		my_mlx_pixel_put(world->win, x, y, get_wall_c(c_wall));
		y++;
		height--;
	}
	while (y < world->config->y)
	{
		my_mlx_pixel_put(world->win, x, y, 0x000000);
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