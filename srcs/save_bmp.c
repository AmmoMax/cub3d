/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:16:10 by amayor            #+#    #+#             */
/*   Updated: 2020/11/25 00:03:48 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static int			get_sr_color(t_world *all, int x, int y)
{
	char		*dst;

	dst = all->win->addr + (y * all->win->line_length + x * (all->win->bbp / 8));
	return (*(unsigned int*)dst);
}

static void			header(unsigned char *header_arr, int size,
		t_world *all, int temp)
{
	header_arr[0] = (unsigned char)'B';
	header_arr[1] = (unsigned char)'M';
	header_arr[2] = (unsigned char)size;
	header_arr[3] = (unsigned char)(size >> 8);
	header_arr[4] = (unsigned char)(size >> 16);
	header_arr[5] = (unsigned char)(size >> 24);
	header_arr[10] = (unsigned char)54;
	header_arr[14] = (unsigned char)40;
	header_arr[18] = (unsigned char)temp;
	header_arr[19] = (unsigned char)(temp >> 8);
	header_arr[20] = (unsigned char)(temp >> 16);
	header_arr[21] = (unsigned char)(temp >> 24);
	header_arr[22] = (unsigned char)all->config->y;
	header_arr[23] = (unsigned char)(all->config->y >> 8);
	header_arr[24] = (unsigned char)(all->config->y >> 16);
	header_arr[25] = (unsigned char)(all->config->y >> 24);
	header_arr[26] = (unsigned char)1;
	header_arr[28] = (unsigned char)24;
}

static void			screen(t_world *all, int fd, int res)
{
	int				color;
	int				x;
	int				y;
	int				size_x;

	color = 0;
	x = 0;
	y = all->config->y - 1;
	size_x = res;
	while (y >= 0)
	{
		while (x < size_x)
		{
			color = get_sr_color(all, x, y);
			write(fd, &color, 3);
			x++;
		}
			y--;
			x = 0;
	}
}

int					make_screen(t_world *all)
{
	int				fd;
	unsigned char	header_arr[54];
	int				count;
	int				size;
	int				temp_res;
	temp_res = all->config->y;
	if (all->config->y % 4)
	 temp_res = all->config->y - (all->config->y % 4);
	size = temp_res * all->config->y + 54;
	count = 0;
	if ((fd = open("./screenshot.bmp", O_RDWR | O_CREAT, 0666)) < 0)
	 return (-1);
	while (count < 54)
	{
	 header_arr[count] = (unsigned char)0;
	 count++;
	}
	header(header_arr, size, all, temp_res);
	write(fd, header_arr, 54);
	screen(all, fd, temp_res);
	close(fd);
	exit(0);
}
