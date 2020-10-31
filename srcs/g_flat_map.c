/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flat_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:24:26 by amayor            #+#    #+#             */
/*   Updated: 2020/10/31 15:35:37 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void		draw_block(t_data *img, int side, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < side)
	{
		j = 0;
		while (j < side)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

int	draw_flat_map(char **map)
{
	// void	*mlx;
	t_data	img;
	t_vars	vars;
	int		i;
	int		j;
	int		x;
	int		y;
	
	i = 0;
	j = 0;
	x = 100;
	y = 100;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 600, "Cub3D");
	img.img = mlx_new_image(vars.mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == '1' || map[i][j] == '2')
			{
				draw_block(&img, 20, 0xFF1493);
				mlx_put_image_to_window(vars.mlx, vars.win, img.img, x, y);
				x += 20;
				j++;
			}
			else
			{
				j++;
				x += 20;
			}
		}
		y += 20;
		x = 100;
		printf("print line map = %s\n", map[i]);
		i++;
	}
	mlx_loop(vars.mlx);
	return (0);
}

