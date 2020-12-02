/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flat_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:24:26 by amayor            #+#    #+#             */
/*   Updated: 2020/11/27 14:49:33 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static int		get_floor_color(t_config *config)
{
	return ((config->floor->red << 16) + \
		(config->floor->green << 8) + config->floor->blue);
}

static int		get_ceiling_color(t_config *config)
{
	return ((config->ceiling->red << 16) +
		(config->ceiling->green << 8) + config->ceiling->blue);
}

static float	set_x(t_xpm *tex, t_plr *ray, char c_wall)
{
	float		x_tex;

	if (c_wall == 'E' || c_wall == 'W')
		x_tex = (int)ray->y % tex->width;
	else
		x_tex = (int)ray->x % tex->width;
	return (x_tex);
}

static t_xpm	*set_tex_coor(t_world *world, char c_wall,
								float y_tex, t_plr *ray)
{
	t_xpm		*tex;
	float		y_t_end;

	tex = set_textures(world, c_wall);
	tex->x_tex = set_x(tex, ray, c_wall);
	if (ray->height > world->config->y)
	{
		y_t_end = (int)(ray->height - y_tex);
		tex->y_t_end = (y_t_end * tex->height) / ray->height;
		tex->y_tex = (y_tex * tex->height) / ray->height;
		tex->step = (tex->y_t_end - tex->y_tex) / world->config->y;
	}
	else
	{
		tex->y_t_end = tex->height;
		tex->step = tex->height / ray->height;
		tex->y_tex = (y_tex * tex->height) / ray->height;
	}
	return (tex);
}

void			draw_column_tex(t_world *world, float x_screen,
								char c_wall, t_plr *ray)
{
	float		y_start;
	float		y_screen;
	float		y_tex;
	t_xpm		*tex;

	set_y_start(world, &ray);
	y_tex = ray->y_tex;
	y_start = ray->y_start;
	y_screen = 0;
	while (y_screen < y_start)
	{
		my_mlx_pixel_put(world->win, x_screen, y_screen,
							get_ceiling_color(world->config));
		y_screen++;
	}
	tex = set_tex_coor(world, c_wall, y_tex, ray);
	get_tex_pix_v2(world, x_screen, &y_start, tex);
	while (y_start < world->config->y)
	{
		my_mlx_pixel_put(world->win, x_screen, y_start,
							get_floor_color(world->config));
		y_start++;
	}
}
