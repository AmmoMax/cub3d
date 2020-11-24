/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_3d_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:53:16 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 23:50:28 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

void		draw_3d_map(t_world *world, int save_flag)
{
	cast_rays_dda(world);
	sprite_finder(world);
	if (save_flag)
		make_screen(world);
	mlx_do_sync(world->win->mlx);
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}

int			get_tex_pix_v2(t_world *world, float x, float *y, t_xpm *tex)
{
	float	x_tex;
	int		color;
	float	y_t_end;
	float	y_tex;

	y_tex = tex->y_tex;
	y_t_end = tex->y_t_end;
	x_tex = tex->x_tex;
	while(y_tex < y_t_end)
	{
		color = my_mlx_get_color(tex, (int)x_tex, (int)y_tex);
		my_mlx_pixel_put(world->win, x, (*y), color);
		(*y)++;
		y_tex += tex->step;
	}
	return (0);
}

void		set_y_start(t_world *world, t_plr **ray)
{
	float	tmp_height;

	tmp_height = (*ray)->height;
	if ((*ray)->height > world->config->y)
	{
		(*ray)->y_start = 0;
		(*ray)->y_tex = ((*ray)->height - world->config->y) / 2;
	}
	else
	{
		(*ray)->y_start = world->config->y / 2 - tmp_height / 2;
		(*ray)->y_tex = 0;
	}
}

t_xpm		*set_textures(t_world *world, char c_wall)
{
	t_xpm	*tex;

	if (c_wall == 'E')
		tex = world->t->e_tex;
	else if (c_wall == 'W')
		tex = world->t->w_tex;
	else if (c_wall == 'S')
		tex = world->t->s_tex;
	else
		tex = world->t->n_tex;
	return (tex);
}
