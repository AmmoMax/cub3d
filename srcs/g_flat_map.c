/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flat_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:24:26 by amayor            #+#    #+#             */
/*   Updated: 2020/11/12 19:56:39 by amayor           ###   ########.fr       */
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

static int	get_tex_pix(t_world *world, float x, float *y, float height, t_plr *ray, char c_wall)
{
	float	step;
	float	x_tex;
	float	y_tex;
	int		color;
	t_xpm *tex;
	float pos;
	
	tex = world->t->e_tex;
	pos = 0;	
	if(c_wall == 'E' || c_wall == 'W') // вертикальная стенка
		x_tex = (int)ray->y % SCALE;
		// x_tex = (int)(*y) % SCALE;
	else
		x_tex = (int)ray->x % SCALE;
		// x_tex = (int)x % SCALE;
	step = (tex->height / height); // проверить не будет ли здесь ошибки при каких то условиях
	y_tex = 0;
	while(height > 0)
	{
		// y_tex = (int)x_tex + tex->width * (int)pos;
		// y_tex = pos;
		// color = tex->tex_pix[pos];
		color = my_mlx_get_color(tex, (int)x_tex, (int)y_tex);
		// color = *(tex->addr + ((int)y_tex * tex->line_length + (int)x_tex * (tex->bbp / 8)));
		my_mlx_pixel_put(world->win, x, (*y), color);
		(*y)++;
		height--;
		y_tex += step;
		// if (height == 5)
			// printf("1");
	}
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
		// my_mlx_pixel_put(world->win, x, y, world->t->e_tex->tex_pix[2]);
		y++;
		height--;
	}
	while (y < world->config->y)
	{
		my_mlx_pixel_put(world->win, x, y, 11796480);
		y++;
	}
}

void		draw_column_tex(t_world *world, float x, float height, char c_wall, t_plr *ray)
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
	get_tex_pix(world, x, &y, height, ray, c_wall);
	while (y < world->config->y)
	{
		my_mlx_pixel_put(world->win, x, y, 0x9932CC);
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
	cast_rays_dda(world);
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}