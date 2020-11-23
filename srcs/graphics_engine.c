/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_engine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:25:15 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 01:15:03 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static t_world	*world_init(t_win **win, m_config **config)
{
	t_world		*world;

	if (!(world = (t_world *)ft_calloc(1, sizeof(t_world))))
	{
		cleanup_win(win);
		clean_config_all(config);
		return (NULL);
	}
	if (!(world->dist_wall = (float *)malloc(sizeof(float) * (*config)->x)))
	{
		cleanup_win(win);
		clean_config_all(config);
		free(world);
		return (NULL);
	}
	return (world);
}

static t_win	*win_init(m_config **c, int save_flag)
{
	t_win		*win;

	if (!(win = (t_win *)ft_calloc(1, sizeof(t_win))))
	{
		clean_config_all(c);
		return (NULL);
	}
	win->mlx = mlx_init();
	check_resolution(win->mlx, c);
	if (!save_flag)
		win->win = mlx_new_window(win->mlx, (*c)->x, (*c)->y, "Cub3D");
	win->img = mlx_new_image(win->mlx, (*c)->x, (*c)->y);
	win->addr = mlx_get_data_addr(win->img, &win->bbp, &win->line_length, &win->endian);
	return (win);
}

/*
** Точка входа в отрисовку графики.
** Принимает указатель на общий конфиг с настройками.
** Создает внутри себя структуры для графики и запускает нужные функции отрисовки.
*/
int				g_engine(m_config *config, int save_flag)
{
	t_win		*win;
	t_world		*world;
	t_plr		plr;
	int			res;

	if (!(win = win_init(&config, save_flag)))
		return (ERR_MEMALLOC);
	if (!(world = world_init(&win, &config)))
		return (ERR_MEMALLOC);
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
