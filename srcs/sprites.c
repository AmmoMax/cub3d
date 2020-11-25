/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:42:37 by amayor            #+#    #+#             */
/*   Updated: 2020/11/25 22:00:07 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void		set_pixel_sprite(t_world *world, t_sprite *sprite, int i, int *j)
{
	int			x;
	int			y;
	float		sprite_size;
	int			color;

	sprite_size = (world->config->x / 2) / tan(FOV / 2) * (SCALE / sprite->dist);
	x = (world->config->x / 2) - (world->config->x / (FOV * 180 / M_PI))*((sprite->dir - world->plr->dir) * 180 / M_PI) - sprite_size / 2;
	y = world->config->y / 2 - sprite_size / 2;
	while (*j < sprite_size)
	{
		if (y + *j < 0 || y + *j > world->config->y)
		{
			(*j)++;
			continue;
		}
		if (sprite->dist < world->dist_wall[(int)(x + i)])
		{
			color = my_mlx_get_color(world->t->sprite_tex, i * world->t->w_tex->width / sprite_size, (*j) * world->t->w_tex->height / sprite_size);
			if (color == -16777216 || color == 0)
			{
				(*j)++;
				continue;
			}
			my_mlx_pixel_put(world->win, x + i, y + (*j), color);
			(*j)++;
		}
		else
			break;
	}
}

static void		draw_sprite(t_world *world, t_sprite *sprite, int i, int j)
{
	int			x;
	int			y;
	float		sprite_size;
	// int			color;

	sprite_size = (world->config->x / 2) / tan(FOV / 2) * (SCALE / sprite->dist);
	x = (world->config->x / 2) - (world->config->x / (FOV * 180 / M_PI))*((sprite->dir - world->plr->dir) * 180 / M_PI) - sprite_size / 2;
	y = world->config->y / 2 - sprite_size / 2;
	while (i < sprite_size)
	{
		j = 0;
		if (x + i < 0 || x + i > world->config->x)
		{
			i++;
			continue;
		}
		set_pixel_sprite(world, sprite, i, &j);
		i++;
	}
}


static void		sprite_sort(t_world *world)
{
	t_sprite	*tmp;
	t_sprite	*sprite_max;
	float		dist_max;

	dist_max = 0;
	while (dist_max != -1)
	{
		tmp = world->sprites;
		dist_max = -1;
		while (tmp)
		{
			if (tmp->dist > dist_max)
			{
				dist_max = tmp->dist;
				sprite_max = tmp;
			}
			tmp = tmp->next;
		}
		if (dist_max != -1)
		{
			draw_sprite(world, sprite_max, 0, 0);
			sprite_max->dist = -1;
		}
	}
}

void			sprite_finder(t_world *world)
{
	t_sprite	*tmp;

	tmp = world->sprites;
	while (tmp)
	{
		tmp->dir = atan2(world->plr->y - tmp->y, tmp->x - world->plr->x);
		if (tmp->dir < 0 && world->plr->dir >= M_PI / 6 && world->plr->dir <= (M_PI * 2 - M_PI / 6))
			tmp->dir += 2 * M_PI;
		if (world->plr->dir > (M_PI * 2 - M_PI / 6) && world->plr->dir <= 7)
			tmp->dir += 2 * M_PI;
		if ((tmp->dir - world->plr->dir - FOV / 2) < (FOV / 2) || (tmp->dir - world->plr->dir + FOV / 2) > (- FOV / 2))
			tmp->dist = sqrt(pow(world->plr->x - tmp->x, 2) + pow(world->plr->y - tmp->y, 2));
	else
		tmp->dist = -1;
	if (tmp->dist > 0 && tmp->dist < SCALE / 7)
		tmp->dist = -1;
	tmp = tmp->next;
	}
	sprite_sort(world);
}
