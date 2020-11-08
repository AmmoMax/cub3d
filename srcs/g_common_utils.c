/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_common_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:24:56 by amayor            #+#    #+#             */
/*   Updated: 2020/11/08 15:06:32 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void save_plr_dir(char plr, t_world **world)
{
	if (plr == 'S')
		(*world)->plr->dir = M_PI_2;
	if (plr == 'W')
		(*world)->plr->dir = M_PI;
	if (plr == 'N')
		(*world)->plr->dir = (3 * M_PI) / 2;
	if (plr == 'E')
		(*world)->plr->dir = 2 * M_PI;
}

/*
** Помещает "пиксель на изображение", вычисляет адрес смещения
** относительно окна и записывает туда цвет.
** Изначально line_length будет отличаться от фактической ширины окна
*/
void		my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bbp / 8));
	*(unsigned int *)dst = color;
}


void		save_plr_pos(t_world **world)
{
	char	**map;
	size_t	i;
	size_t	j;

	map = (*world)->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S')
			{
				(*world)->plr->x = j * SCALE + START_X;
				(*world)->plr->y = i * SCALE + START_Y;
				save_plr_dir(map[i][j], world);
				return ;
			}
			j++;
		}
		i++;
	}
}

void		check_location(t_world **p_world, float new_x, float new_y)
{
	int		i;
	int		j;
	t_world	*world;	

	world = *p_world;
	i = (int)(new_y - START_Y) / SCALE;
	j = (int)(new_x - START_X) / SCALE;
	if ((world->map[i][(int)(world->plr->x - START_X) / SCALE] != '1'))
		world->plr->y = new_y;
	if ((world->map[(int)(world->plr->y - START_Y) / SCALE][j] != '1'))
		world->plr->x = new_x;
}

static int		get_dist(t_plr *ray, t_world *world)
{
	float		dist;
	float		dist2;
	float		height;
	float		plane;
	t_plr		*plr;

	plr = world->plr;
	plane = (world->config->x / 2) / tan(FOV / 2);
	dist = sqrt (pow(ray->x - plr->x, 2) + pow(ray->y - plr->y, 2));
	dist2 = abs((int)(dist * cos(ray->start - ray->dir)));
	height = (SCALE / dist2) * plane;
	// height = 1080 / dist * 10;
	return ((int)height);
}


// TODO: скорее всего не нужна, может быть стоит убрать
void		cast_ray(t_world *world)
{
	t_plr	ray;
	float	height;

	ray = (*world->plr);
	while(world->map[(int)((ray.y - START_Y) / SCALE)][(int)((ray.x - START_X) / SCALE)] != '1')
	{
		ray.x += cos(ray.dir);
		ray.y += sin(ray.dir);
		// my_mlx_pixel_put(world->win, ray.x, ray.y, 0x990099);
	}
	height = get_dist(&ray, world);
	// draw_column(world, height, 0xFFFFFF);
}

/*
** Кастует лучи для плоской карты по простому алгоритму синусов-косинусов.
** 
*/
void		cast_rays_flat(t_world *world)
{
	t_plr	ray;
	float	height;
	int		x = 0;

	ray = *world->plr;
	ray.start = world->plr->dir - (FOV / 2);
	ray.end = world->plr->dir + (FOV / 2);
	while(ray.start < ray.end)
	{
		ray.x = world->plr->x;
		ray.y = world->plr->y;
		while (world->map[(int)((ray.y - START_Y) / SCALE)][(int)((ray.x - START_X) / SCALE)] != '1')
		{
			ray.x = ray.x + cos(ray.start);
			ray.y = ray.y + sin(ray.start);
			my_mlx_pixel_put(world->win, ray.x, ray.y, 0x990099);
		}
		height = get_dist(&ray, world);
		x++;
		ray.start += FOV / world->config->x;
	}
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}

void		cast_rays(t_world *world)
{
	t_plr	ray;
	float	height;
	int		x = 0;

	ray = *world->plr;
	ray.start = world->plr->dir - (FOV / 2);
	ray.end = world->plr->dir + (FOV / 2);
	while(ray.start < ray.end)
	{
		ray.x = world->plr->x;
		ray.y = world->plr->y;
		while (world->map[(int)((ray.y - START_Y) / SCALE)][(int)((ray.x - START_X) / SCALE)] != '1')
		{
			ray.x = ray.x + cos(ray.start);
			ray.y = ray.y + sin(ray.start);
		}
		height = get_dist(&ray, world);
		draw_column(world, x, height, 0xFFFFFF);
		x++;
		ray.start += FOV / world->config->x;
	}
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}