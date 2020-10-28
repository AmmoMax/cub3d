#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_data
{
	void 		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct s_world
{
	t_vars	*vars;
	t_data	*img;
	int		x;
	int		y;
}				t_world;


void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void		draw_square(t_data *img, int side, int color)
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

int			render_next_frame(t_world *world)
{
	draw_square(world->img, 200, 0xDC143C);
	mlx_put_image_to_window(world->vars->mlx, world->vars->win, world->img->img, 100, 100);
	sleep(1);
	world->img->img = mlx_new_image(world->vars->mlx, 800, 600);
	world->img->addr = mlx_get_data_addr(world->img->img, &(world->img->bits_per_pixel), &(world->img->line_length), &(world->img->endian));
	draw_square(world->img, 200, 0xFFFF00);
	mlx_put_image_to_window(world->vars->mlx, world->vars->win, world->img->img, 100, 100);
	sleep(1);

}

int			handle_keypress(int keycode, t_world *world)
{
	// printf("keycode = %d\n", keycode);
	if (keycode == 65362)
	{
		mlx_clear_window(world->vars->mlx, world->vars->win);
		draw_square(world->img, 200, 0xDC143C);
		mlx_put_image_to_window(world->vars->mlx, world->vars->win, world->img->img, world->x, world->y);
		world->x += 10;
		// world->img->img = mlx_new_image(world->vars->mlx, 800, 600);
		// mlx_destroy_image(world->vars->mlx, world->img->img);
		// world->y += 10;
	}
}

int main(void)
{
	void	*mlx;
	t_data	img;
	t_vars	vars;
	int		color;
	t_world	world;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 600, "Test animation");

	img.img = mlx_new_image(vars.mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	world.img = &img;
	world.vars = &vars;
	world.x = 100;
	world.y = 100;
	// draw_square(&img, 100, 0x20B2AA);
	// mlx_put_image_to_window(world.vars->mlx, world.vars->win, world.img->img, 100, 100);
	// mlx_loop_hook(vars.mlx, render_next_frame, &world);
	mlx_hook(world.vars->win, 2, 1L<<0, handle_keypress, &world);
	mlx_loop(vars.mlx);
}