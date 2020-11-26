/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_common_utils_p2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:24:06 by amayor            #+#    #+#             */
/*   Updated: 2020/11/26 13:24:13 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

int			close_red_cross(t_world **world)
{
	printf("Close the window by red cross!\n");
	cleanup_all_world(world);
	free(*world);
	*world = NULL;
	exit(0);
}

int			close_esc(t_world **world)
{
	printf("Close the window by Esc!\n");
	cleanup_all_world(world);
	free(*world);
	*world = NULL;
	exit(0);
}

/*
** Помещает "пиксель на изображение", вычисляет адрес смещения
** относительно окна и записывает туда цвет.
** Изначально line_length будет отличаться от фактической ширины окна
*/

void		my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bbp / 8));
	*(unsigned int *)dst = color;
}

int			my_mlx_get_color(t_xpm *tex, int x, int y)
{
	char	*dst;
	int		color;

	dst = tex->addr + (y * tex->line_length + x * (tex->bbp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
