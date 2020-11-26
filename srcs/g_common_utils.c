/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_common_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:24:56 by amayor            #+#    #+#             */
/*   Updated: 2020/11/26 13:26:12 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void	save_plr_dir(char plr, t_world **world)
{
	if (plr == 'N')
		(*world)->plr->dir = M_PI_2;
	if (plr == 'W')
		(*world)->plr->dir = M_PI;
	if (plr == 'S')
		(*world)->plr->dir = (3 * M_PI) / 2;
	if (plr == 'E')
		(*world)->plr->dir = 0;
}

void		save_plr_pos(t_world **world)
{
	char	**map;
	size_t	i;
	size_t	j;

	map = (*world)->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' ||
					map[i][j] == 'E' || map[i][j] == 'S')
			{
				(*world)->plr->x = j * SCALE + START_X + (SCALE / 2);
				(*world)->plr->y = i * SCALE + START_Y + (SCALE / 2);
				save_plr_dir(map[i][j], world);
				return ;
			}
			j++;
		}
		i++;
	}
}

void		check_location(t_world **p_world, float new_x, float new_y)
{
	int		i;
	int		j;
	t_world	*world;

	world = *p_world;
	i = (int)(new_y) / SCALE;
	j = (int)(new_x) / SCALE;
	if ((world->map[i][(int)world->plr->x / SCALE] != '1'))
		world->plr->y = new_y;
	if ((world->map[(int)world->plr->y / SCALE][j] != '1'))
		world->plr->x = new_x;
}

int			check_plr_pos(t_world *world, int x, int y)
{
	if ((x == (int)world->plr->x) && y == (int)world->plr->y)
		return (1);
	else if (((int)world->plr->y > y) && ((int)world->plr->y < (y + SCALE)) &&
													(int)world->plr->x == x)
		return (1);
	else
		return (0);
}

void		check_resolution(void *mlx, m_config **config)
{
	int sizex;
	int sizey;

	mlx_get_screen_size(mlx, &sizex, &sizey);
	if ((*config)->x > sizex || (*config)->x < 0 ||
					(*config)->y > sizey || (*config)->y < 0)
	{
		(*config)->x = sizex;
		(*config)->y = sizey;
	}
}
