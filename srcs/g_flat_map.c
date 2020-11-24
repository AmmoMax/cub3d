/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flat_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:24:26 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 13:23:27 by amayor           ###   ########.fr       */
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

// static int get_wall_c(char c_wall)
// {
// 	if (c_wall == 'N')
// 		return (0x00FFFF);
// 	if (c_wall == 'S')
// 		return (0xFFD700);
// 	if (c_wall == 'E')
// 		return (0xFF4500);
// 	if (c_wall == 'W')
// 		return (0x8A2BE2);
// 	return (0);
// }

static int	get_floor_color(m_config *config)
{
	return ((config->floor->red << 16) + (config->floor->green << 8) +  config->floor->blue);
}

static int	get_ceiling_color(m_config *config)
{
	return ((config->ceiling->red << 16) + (config->ceiling->green << 8) +  config->ceiling->blue);
}

static int	get_tex_pix_v2(t_world *world, float x, float *y, float height, t_plr *ray, char c_wall, float y_tex)
{
	float	step;
	float	x_tex;
	float	y_t_end;
	int		color;
	t_xpm *tex;

	if (c_wall == 'E')
		tex = world->t->e_tex;
	else if (c_wall == 'W')
		tex = world->t->w_tex;
	else if (c_wall == 'S')
		tex = world->t->s_tex;
	else
		tex = world->t->n_tex;
	if(c_wall == 'E' || c_wall == 'W') // вертикальная стенка
		x_tex = (int)ray->y % tex->width;
	else
		x_tex = (int)ray->x % tex->width;
	if (height > world->config->y)
	{
		y_t_end = (int)(height - y_tex);
		y_t_end = (y_t_end * tex->height) / height;
		y_tex = (y_tex * tex->height) / height;
		step = (y_t_end - y_tex) / world->config->y;
	}
	else
	{
		y_t_end = tex->height;
		step = tex->height / height;
		y_tex = (y_tex * tex->height) / height;
	}
	while(y_tex < y_t_end)
	{
		color = my_mlx_get_color(tex, (int)x_tex, (int)y_tex);
		my_mlx_pixel_put(world->win, x, (*y), color);
		(*y)++;
		y_tex += step;
	}
	return (0);
}


// void		draw_column(t_world *world, float x, float height, char c_wall)
// {
// 	float y_start;
// 	float y;

// 	if (height > world->config->y)
// 		height = world->config->y;
// 	y_start = world->config->y / 2 - height / 2;
// 	y = 0;
// 	while (y < y_start)
// 	{
// 		my_mlx_pixel_put(world->win, x, y, get_ceiling_color(world->config));
// 		y++;
// 	}
// 	while (height > 0)
// 	{
// 		my_mlx_pixel_put(world->win, x, y, get_wall_c(c_wall));
// 		// my_mlx_pixel_put(world->win, x, y, world->t->e_tex->tex_pix[2]);
// 		y++;
// 		height--;
// 	}
// 	while (y < world->config->y)
// 	{
// 		my_mlx_pixel_put(world->win, x, y, get_floor_color(world->config));
// 		y++;
// 	}
// }

void		draw_column_tex(t_world *world, float x_screen, float height, char c_wall, t_plr *ray)
{
	float y_start;
	float y_screen;
	float y_tex;
	float	tmp_height;

	tmp_height = height;
	if (height > world->config->y)
	{
		y_start = 0;
		y_tex = (height - world->config->y) / 2; //точка с которой начинаем отрисовку текстуры
		// tmp_height = world->config->y;
	}
	else
	{
		// y_col = 0;
		// tmp_height = height;
		y_start = world->config->y / 2 - tmp_height / 2;
		y_tex = 0;
	}
	y_screen = 0;
	while (y_screen < y_start)
	{
		my_mlx_pixel_put(world->win, x_screen, y_screen, get_ceiling_color(world->config));
		y_screen++;
	}
	// get_tex_pix(world, x, &y, height, ray, c_wall);
	get_tex_pix_v2(world, x_screen, &y_start, tmp_height, ray, c_wall, y_tex);
	while (y_start < world->config->y)
	{
		my_mlx_pixel_put(world->win, x_screen, y_start, get_floor_color(world->config));
		y_start++;
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

void			check_resolution(void*mlx, m_config **config)
{
	int sizex;
	int sizey;

	mlx_get_screen_size(mlx, &sizex, &sizey);
	if ((*config)->x > sizex || (*config)->x < 0 || (*config)->y > sizey || (*config)->y < 0)
	{
		(*config)->x = sizex;
		(*config)->y = sizey;
	}
}

void	draw_3d_map(t_world *world, int save_flag)
{
	cast_rays_dda(world);
	sprite_finder(world);
	if (save_flag)
		make_screen(world);
	mlx_do_sync(world->win->mlx);
	mlx_put_image_to_window(world->win->mlx, world->win->win, world->win->img, START_X, START_Y);
}
