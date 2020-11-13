/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:18:12 by amayor            #+#    #+#             */
/*   Updated: 2020/11/12 22:51:02 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"


static int			find_wall(t_world *world, float x, float y)
{
	x = (int)x / SCALE;
	y = (int)y / SCALE;

	if (x > world->config->max_x - 1 || y > world->config->max_y - 1 ||
							x < 0 || y < 0 || world->map[(int)y][(int)x] == ' ')
		return (-1);
	else if (world->map[(int)y][(int)x] == '1')
		return (1);
	else
		return (0);
}

static int		get_height(t_world *world, float dist)
{
	float		height;
	float		plane;

	plane = (world->config->x / 2) / tan(FOV / 2);
	height = (SCALE / dist) * plane;
	return ((int)height);
}

/*
** Проверяет горизонтальные пересечения для каждого луча.
** Возвращает расстояние для стены.
*/
static float		hor_intersect(t_world *world, t_plr *ray, char *h_wall)
{
	float	step_y;
	float	step_x;
	float	p_x;
	float	p_y;
	int		res;

	step_y = SCALE;
	step_x = SCALE / tan(ray->start);
	if ((ray->start < M_PI && ray->start > 0) || ray->start > M_PI * 2) // луч идет вверх
	{
		*h_wall = 'S';
		p_y = (int)world->plr->y / SCALE * SCALE - 0.001;
		step_y = -step_y;
	}
	else
	{
		*h_wall = 'N';
		p_y = (int)world->plr->y / SCALE * SCALE + SCALE; // луч идет вниз
		step_x = -step_x;
	}
	p_x = world->plr->x + (world->plr->y - p_y) / tan(ray->start);
	while ((res = find_wall(world, p_x ,p_y)) == 0)
	{
		p_x += step_x;
		p_y += step_y;
	}
	ray->x = p_x;
	// ray->y = p_y;
	if (res == -1)
		return (1000000);
	return (sqrt(pow(world->plr->x - p_x, 2) + pow(world->plr->y - p_y, 2)));	
}



static float		vert_intersect(t_world *world, t_plr *ray, char *v_wall)
{
	float	step_y;
	float	step_x;
	float	p_x;
	float	p_y;
	int		res;

	step_x = SCALE;
	step_y = SCALE * tan(ray->start);
	if (ray->start > M_PI_2 && ray->start < (3 * M_PI / 2)) // луч движется влево
	{
		*v_wall = 'E';
		p_x = (int)world->plr->x / SCALE * SCALE - 0.001;
		step_x = -step_x;
	}
	else
	{
		*v_wall = 'W';
		p_x = (int)world->plr->x / SCALE * SCALE + SCALE; // луч движется вправо
		step_y = -step_y; // из за перевернутой системы координат?
	}
	p_y = world->plr->y + (world->plr->x - p_x) * tan(ray->start);
	while ((res = find_wall(world, p_x, p_y)) == 0)
	{
		p_x += step_x;
		p_y += step_y;
	}
	// ray->x = p_x;
	ray->y = p_y;
	if (res == -1)
		return (1000000);
	return (sqrt(pow(world->plr->x - p_x, 2) + pow(world->plr->y - p_y, 2)));	
}


/*
** Кастует веер лучей по ширине заданного в конфиге разрешения.
** Для каждого луча рисует вертикальный столбец нужной высоты.
**
*/
void		cast_rays_dda(t_world *world)
{
	t_plr	ray;
	float	dist_hor;
	float	dist_vert;
	int		x;
	float	height;
	char	v_wall;
	char	h_wall;

	ray = *world->plr;
	x = 0;
	ray.end = world->plr->dir - (FOV / 2);
	ray.start = world->plr->dir + (FOV / 2);
	while(ray.start > ray.end)
	{
		ray.x = world->plr->x;
		ray.y = world->plr->y;
		
		dist_hor = hor_intersect(world, &ray, &h_wall);
		dist_vert = vert_intersect(world, &ray, &v_wall);
		if (dist_hor < dist_vert)
		{
			height = get_height(world, dist_hor * cos(ray.start - world->plr->dir));
			// draw_column(world, x, height, h_wall);
			draw_column_tex(world, x, height, h_wall, &ray);
		}
		else
		{
			height = get_height(world, dist_vert * cos(ray.start - world->plr->dir));
			// draw_column(world, x, height, v_wall);
			draw_column_tex(world, x, height, v_wall, &ray);
		}
		x++;
		ray.start -= FOV / world->config->x;
	}
	// mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}

