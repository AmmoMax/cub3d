/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:55:38 by amayor            #+#    #+#             */
/*   Updated: 2020/11/02 11:51:13 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
#define SCALE 30
#define START_X 100
#define START_Y 100
#define CLR_BLK 0xFF1497
#define CLR_PLR 0x00FFFF

typedef struct 			s_win
{
	void				*mlx;
	void				*win;
	void 				*img;
	char				*addr;
	int					bbp;
	int					line_length;
	int					endian;
}						t_win;

typedef struct 			s_plr
{
	float				x;
	float				y;
	float				dir;
	float				start;
	float				end;
}						t_plr;

typedef struct			s_world
{
	t_plr				*plr;
	t_win				*win;
	char				**map;
}						t_world;


/* Graphics utils */

int			g_engine(m_config *config);
void		my_mlx_pixel_put(t_win *win, int x, int y, int color);
void		draw_flat_map(t_world *world);
void		save_plr_pos(t_world **world);
void		print_maps_block(t_world *world, int x, int y);
int			move_f(int keycode, t_world **world);


#endif