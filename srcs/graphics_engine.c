/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_engine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:25:15 by amayor            #+#    #+#             */
/*   Updated: 2020/11/23 13:16:11 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Точка входа в отрисовку графики.
** Принимает указатель на общий конфиг с настройками.
** Создает внутри себя структуры для графики и запускает нужные функции отрисовки.
*/
int			g_engine(m_config *config, int save_flag)
{
	t_win	*win;
	t_world	*world;
	t_plr	plr;
	int		res;
	
	if (!(win = (t_win *)ft_calloc(1, sizeof(t_win))))
	{
		clean_config_all(&config);
		return (ERR_MEMALLOC);
	}
	win->mlx = mlx_init();
	check_resolution(win->mlx, &config);
	if (!save_flag)
		win->win = mlx_new_window(win->mlx, config->x, config->y, "Cub3D");
	win->img = mlx_new_image(win->mlx, config->x, config->y);
	win->addr = mlx_get_data_addr(win->img, &win->bbp, &win->line_length, &win->endian);

	if (!(world = (t_world *)ft_calloc(1, sizeof(t_world))))
	{
		cleanup_win(&win);
		clean_config_all(&config);
		return (ERR_MEMALLOC);
	}
	if (!(world->dist_wall = (float *)malloc(sizeof(float) * config->x)))
	{
		cleanup_win(&win);
		clean_config_all(&config);
		free(world);
		return (ERR_MEMALLOC);
	}
	world->map = config->flat_map;
	world->win = win;
	world->plr = &plr;
	world->config = config;
	save_plr_pos(&world);
	if ((res = load_textures_v2(&world)) != 0)
		return (res);
	if ((res = load_sprite(&world)) != 0)
		return (res);
	draw_3d_map(world, save_flag);
	mlx_hook(win->win, 17, 1L<<17, close_red_cross, &world);
	mlx_hook(win->win, 2, 1L<<0, key_handler, &world);
	mlx_loop(win->mlx);
	return (0);
}
