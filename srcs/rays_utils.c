/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:18:12 by amayor            #+#    #+#             */
/*   Updated: 2020/11/26 21:28:50 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void		set_draw_tex(t_world *world, t_plr *ray, char wall, int x)
{
	if (wall == 'S' || wall == 'N')
	{
		ray->height = get_height(world, ray->dist_hor *
							cos(ray->start - world->plr->dir));
		world->dist_wall[x] = ray->dist_hor;
		draw_column_tex(world, x, wall, ray);
	}
	else
	{
		ray->height = get_height(world, ray->dist_vert *
							cos(ray->start - world->plr->dir));
		world->dist_wall[x] = ray->dist_vert;
		draw_column_tex(world, x, wall, ray);
	}
}

static double	find_dist_v(t_world *w, t_plr *ray)
{
	int res;

	while ((res = find_wall(w, ray->p_x, ray->p_y)) == 0)
	{
		ray->p_x += ray->step_x;
		ray->p_y += ray->step_y;
	}
	ray->y = ray->p_y;
	if (res == -1)
		return (1000000);
	return (sqrt(pow(w->plr->x - ray->p_x, 2) + pow(w->plr->y - ray->p_y, 2)));
}

/*
** Проверяет горизонтальные пересечения для каждого луча.
** Возвращает расстояние для стены.
*/

static float	hor_intersect(t_world *world, t_plr *ray, char *h_wall)
{
	ray->step_y = SCALE;
	ray->step_x = SCALE / tan(ray->start);
	if ((ray->start < M_PI && ray->start > 0) || ray->start > M_PI * 2)
	{
		*h_wall = 'S';
		ray->p_y = (int)world->plr->y / SCALE * SCALE - 0.001;
		ray->step_y = -ray->step_y;
	}
	else
	{
		*h_wall = 'N';
		ray->p_y = (int)world->plr->y / SCALE * SCALE + SCALE;
		ray->step_x = -ray->step_x;
	}
	ray->p_x = world->plr->x + (world->plr->y - ray->p_y) / tan(ray->start);
	return (find_dist_h(world, ray));
}

static float	vert_intersect(t_world *world, t_plr *ray, char *v_wall)
{
	ray->step_x = SCALE;
	ray->step_y = SCALE * tan(ray->start);
	if (ray->start > M_PI_2 && ray->start < (3 * M_PI / 2))
	{
		*v_wall = 'E';
		ray->p_x = (int)world->plr->x / SCALE * SCALE - 0.001;
		ray->step_x = -ray->step_x;
	}
	else
	{
		*v_wall = 'W';
		ray->p_x = (int)world->plr->x / SCALE * SCALE + SCALE;
		ray->step_y = -ray->step_y;
	}
	ray->p_y = world->plr->y + (world->plr->x - ray->p_x) * tan(ray->start);
	return (find_dist_v(world, ray));
}

/*
** Кастует веер лучей по ширине заданного в конфиге разрешения.
** Для каждого луча рисует вертикальный столбец нужной высоты.
*/

void			cast_rays_dda(t_world *world)
{
	t_plr		ray;
	int			x;
	char		v_wall;
	char		h_wall;

	ray = *world->plr;
	x = 0;
	ray.end = world->plr->dir - (FOV / 2);
	ray.start = world->plr->dir + (FOV / 2);
	while (ray.start > ray.end)
	{
		ray.x = world->plr->x;
		ray.y = world->plr->y;
		ray.dist_hor = hor_intersect(world, &ray, &h_wall);
		ray.dist_vert = vert_intersect(world, &ray, &v_wall);
		if (ray.dist_hor < ray.dist_vert)
			set_draw_tex(world, &ray, h_wall, x);
		else
			set_draw_tex(world, &ray, v_wall, x);
		x++;
		ray.start -= FOV / world->config->x;
	}
}
