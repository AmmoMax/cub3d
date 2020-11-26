/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 00:21:48 by amayor            #+#    #+#             */
/*   Updated: 2020/11/26 22:24:31 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

int		local_print_error(int err)
{
	print_err(err);
	return (err);
}

double	find_dist_h(t_world *w, t_plr *ray)
{
	int res;

	while ((res = find_wall(w, ray->p_x, ray->p_y)) == 0)
	{
		ray->p_x += ray->step_x;
		ray->p_y += ray->step_y;
	}
	ray->x = ray->p_x;
	if (res == -1)
		return (1000000);
	return (sqrt(pow(w->plr->x - ray->p_x, 2) + pow(w->plr->y - ray->p_y, 2)));
}

int		find_wall(t_world *world, float x, float y)
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

int		get_height(t_world *world, float dist)
{
	float		height;
	float		plane;

	plane = (world->config->x / 2) / tan(FOV / 2);
	height = (SCALE / dist) * plane;
	return ((int)height);
}

int		get_sprite_color(t_world *world, int i, int j, t_sprite *s)
{
	return (my_mlx_get_color(world->t->sprite_tex, i *
						world->t->w_tex->width /
				s->sprite_size, j * world->t->w_tex->height / s->sprite_size));
}
