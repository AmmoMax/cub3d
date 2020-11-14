/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_engine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:25:15 by amayor            #+#    #+#             */
/*   Updated: 2020/11/14 20:38:07 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

/*
** Точка входа в отрисовку графики.
** Принимает указатель на общий конфиг с настройками.
** Создает внутри себя структуры для графики и запускает нужные функции отрисовки.
*/
int		g_engine(m_config *config)
{
	t_win	win;
	t_world	*world;
	// t_world	*p_world;
	t_plr	plr;
	
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, config->x, config->y, "Cub3D");
	win.img = mlx_new_image(win.mlx, config->x, config->y);
	win.addr = mlx_get_data_addr(win.img, &win.bbp, &win.line_length, &win.endian);

	if (!(world = (t_world *)malloc(sizeof(t_world))))
		return (ERR_MEMALLOC);
	world->map = config->flat_map;
	world->win = &win;
	world->plr = &plr;
	world->config = config;
	save_plr_pos(&world);
	load_textures_v2(&world);
	load_sprite(&world);
	// draw_flat_map(p_world);
	draw_3d_map(world);

	// mlx_hook(world.win->win, 2, 1L<<0, &move_f, &p_world);
	mlx_hook(world->win->win, 2, 1L<<0, move_forward, &world);
	mlx_loop(win.mlx);
	return (0);
}