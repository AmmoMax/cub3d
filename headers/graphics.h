/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:55:38 by amayor            #+#    #+#             */
/*   Updated: 2020/11/26 21:10:52 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
#define SCALE 64
#define START_X 0
#define START_Y 0
#define CLR_BLK 0xFF1497
#define CLR_PLR 0x00FF00
#define SPEED 5
#define FOV	M_PI / 3
#define _USE_MATH_DEFINES

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
	float				dist_hor;
	float				dist_vert;
	float				height;
	float				y_start;
	float				y_tex;
	float				p_x;
	float				p_y;
	float				step_y;
	float				step_x;
}						t_plr;

typedef struct			s_xpm
{
	void				*img;
	char				*addr;
	int					width;
	int					height;
	float				scale;
	int					bbp;
	int					line_length;
	int					endian;
	int					*tex_pix;
	float				y_t_end;
	float				y_tex;
	float				step;
	float				x_tex;
}						t_xpm;

typedef struct			s_textures
{
	t_xpm				*n_tex;
	t_xpm				*s_tex;
	t_xpm				*e_tex;
	t_xpm				*w_tex;
	t_xpm				*sprite_tex;
}						t_tex;

typedef struct			s_sprite
{
	float				x;
	float				y;
	float				dist;
	float				dir;
	struct s_sprite		*next;
}						t_sprite;

typedef struct			s_world
{
	t_plr				*plr;
	t_win				*win;
	char				**map;
	m_config			*config;
	t_tex				*t;
	t_sprite			*sprites;
	float				*dist_wall;
}						t_world;

/* Graphics utils */

int			g_engine(m_config *config, int save_flag);
void		my_mlx_pixel_put(t_win *win, int x, int y, int color);
void		save_plr_pos(t_world **world);
void		print_maps_block(t_world *world, int x, int y);
void		check_location(t_world **world, float new_x, float new_y);
void		cast_rays(t_world *world);
void		draw_column(t_world *world, float x, float height, char c_wall);
int			key_handler(int keycode, t_world **world);
void		cast_rays_dda(t_world *world);
void		get_textures(t_world *world, t_xpm *texture, char *path);
void		draw_3d_map(t_world *world, int save_flag);
void		draw_column_tex(t_world *world, float x_screen, char c_wall, t_plr *ray);
int			my_mlx_get_color(t_xpm *tex, int x, int y);
int			save_sprites_pos(t_world **world);
int			load_textures_v2(t_world **world);
int			*strcpy_int(int *dst, int *src);
int			load_sprite(t_world **world);
void		sprite_finder(t_world *world);
int			make_screen(t_world *all);
int			close_red_cross(t_world **world);
int			close_esc(t_world **world);
void		check_resolution(void*mlx, m_config **config);
void		cleanup_all_tex(t_tex **p_textures, t_world *world);
void		cleanup_sprites(t_sprite **sprites_head);
void		cleanup_all_world(t_world **p_world);
void		cleanup_win(t_win **win);
void		cleanup_save_sprite_pos(t_world **world);
int		get_tex_pix_v2(t_world *world, float x, float *y, t_xpm *tex);
void	set_y_start(t_world *world, t_plr **ray);
t_xpm	*set_textures(t_world *world, char c_wall);

#endif
