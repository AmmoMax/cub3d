/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:42:37 by amayor            #+#    #+#             */
/*   Updated: 2020/11/17 21:42:15 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

void		draw_sprites(t_world *world, t_sprite *sprite)
{
	float	sprite_dir;
	float	sprite_dist;
	int		sprite_size;
	double		h_offset;
	double		v_offset;
	int		i;
	int		j;

	sprite_dir = atan2(world->plr->y - sprite->y, sprite->x - world->plr->x);
	// if (sprite_dir < 0)
	// 	sprite_dir += 2 * M_PI;
	// if ((world->plr->dir < M_PI / 3 && world->plr->dir > 0)  || (world->plr->dir > (3 * M_PI / 2 + M_PI / 6)))
	// 	sprite_dir += 2 * M_PI;

	if (sprite_dir < 0 && world->plr->dir >= M_PI / 6 && world->plr->dir <= (M_PI * 2 - M_PI / 6))
		sprite_dir += 2 * M_PI;
	if (world->plr->dir > (M_PI * 2 - M_PI / 6) && world->plr->dir <= 7)
		sprite_dir += 2 * M_PI;
	printf("=====\nsprite_dir = %f degrees or %f rad\n", sprite_dir * 180 / M_PI, sprite_dir);
	printf("plr dir = %f degrees or %f rad\n", world->plr->dir * 180 / M_PI, world->plr->dir);
	printf("delta = %f\n", (sprite_dir - world->plr->dir) * 180 / M_PI);
	// while (sprite_dir - world->plr->dir > M_PI)
	// 	sprite_dir -= 2 * M_PI;
	// while (sprite_dir - world->plr->dir < -M_PI)
	// 	sprite_dir += 2 * M_PI;
	if ((sprite_dir - world->plr->dir - FOV / 2) > (FOV / 2) || (sprite_dir - world->plr->dir + FOV / 2) < (- FOV / 2))
		return ;	
	sprite_dist = sqrt(pow(world->plr->x - sprite->x, 2) + pow(world->plr->y - sprite->y, 2));
	// sprite_size = (world->config->y / sprite_dist) * 10; // опасное место - возможно деление на ноль
	sprite_size = (world->config->x / 2) / tan(FOV / 2) * (SCALE / sprite_dist);
	// sprite_size = world->config->y / sprite_dist;
	// h_offset = (sprite_dir - world->plr->dir) * (world->config->x / 2) / FOV + (world->config->x / 2) - sprite_size / 2;
	h_offset = (world->config->x / 2) - (world->config->x / (FOV * 180 / M_PI)) *((sprite_dir - world->plr->dir) * 180 / M_PI) - sprite_size / 2; // еще надо учесть ширину спрайта, предварительно ее посчитав где то
	// h_offset = (world->config->x / FOV) * (sprite_dir - world->plr->dir); // место на x где будет середина спрайта
	v_offset = world->config->y / 2 - sprite_size / 2;
	printf("x: %f, y = %f\n", h_offset, v_offset);
	// v_offset = (world->config->y / 2) - (sprite_size / 2);
	// i = 0;
	// while (i < sprite_size && (i + h_offset) < world->config->x)
	// {
	// 	if (h_offset + i >= 0 || h_offset + i < world->config->x)
	// 	{
	// 		j = 0;
	// 		while (j < sprite_size)
	// 		{
	// 			if (v_offset+j < 0 || v_offset + j>= world->config->y)
	// 				continue;
	// 			// my_mlx_pixel_put(world->win, world->config->x / 2 + h_offset + i, v_offset + j, 0x000000);
	// 			my_mlx_pixel_put(world->win, h_offset + i, v_offset + j, 0x000000);
	// 			j++;
	// 		}
	// 	}
	// 	i++;
	// }
	i = 0;
	while (i < sprite_size)
	{
		j = 0;
		if (h_offset + i < 0 || h_offset + i > world->config->x)
		{
			i++;
			continue;
		}
		while (j < sprite_size)
		{
			if (v_offset + j < 0 || v_offset + j > world->config->y)
			{
			 j++;
			 continue;
			}
			if (sprite_dist < world->dist_wall[(int)(h_offset + i)])
			{
				my_mlx_pixel_put(world->win, h_offset + i, v_offset + j, 0x000000);
				j++;
			}
			else
				break;
		}
		i++;
	}
}

static void		draw_sprite(t_world *world, t_sprite *sprite, int i, int j)
{
	int			x;
	int			y;
	float		sprite_size;
	int			color;

	sprite_size = (world->config->x / 2) / tan(FOV / 2) * (SCALE / sprite->dist);
	x = (world->config->x / 2) - (world->config->x / (FOV * 180 / M_PI)) *((sprite->dir - world->plr->dir) * 180 / M_PI) - sprite_size / 2;
	y = world->config->y / 2 - sprite_size / 2;
	while (i < sprite_size)
	{
		j = 0;
		if (x + i < 0 || x + i > world->config->x)
		{
			i++;
			continue;
		}
		while (j < sprite_size)
		{
			if (y + j < 0 || y + j > world->config->y)
			{
			 j++;
			 continue;
			}
			if (sprite->dist < world->dist_wall[(int)(x + i)])
			{
				// my_mlx_pixel_put(world->win, x + i, y + j, 0x000000 + j - i);
				// uint32_t color = tex_sprites.get(i*tex_sprites.size/sprite_screen_size, j*tex_sprites.size/sprite_screen_size, sprite.tex_id);
				color = my_mlx_get_color(world->t->sprite_tex, i * world->t->w_tex->width / sprite_size, j * world->t->w_tex->height / sprite_size);
				if (color == -16777216 || color == 0)
				{
					j++;
					continue;
				}
				// printf("color = %d\n", color);
				my_mlx_pixel_put(world->win, x + i, y + j, color);
				j++;
			}
			else
				break;
		}
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