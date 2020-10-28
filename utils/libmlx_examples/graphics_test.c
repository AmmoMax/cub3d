#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

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


/*
* Вычисляет смещение памяти относительно line_length.
* Изначально line_length будет отличаться от фактической ширины окна
*/
void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int			key_hook(int keycode, t_vars *vars)
{
	printf("Hello from my key_hook!\n");
	printf("keycode = %d\n", keycode);
}

int			mouse_hook(int code, t_vars *vars)
{
	printf("code from mouse = %d\n", code);
}

int			close_esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
}

int			close_red_cross(int keycode, t_vars *vars)
{
	
	printf("Close the window!\n");
	exit(0);
}

int			mouse_hover(int keycode, t_vars *vars)
{
	printf("Hi mouse!");
}

int			main(void)
{
	void	*mlx;
	t_data	img;
	t_vars	vars;
	// void	*mlx_win;
	int		color;

	vars.mlx = mlx_init();
	/*
	* устанавливает соединение с графической подсистемой и возвращает указатель
	* на адрес нашего текущего экземппляра mlx
	*/
	vars.win = mlx_new_window(vars.mlx, 800, 600, "Hello World!");
	/*
	* возвращает указатель на созданное окно с заданными параметрами
	*/
	img.img = mlx_new_image(vars.mlx, 200, 200);
	/*
	* создает объект изображения определенного размера, в который мы потом
	* сможем поместить байты в нужном виде
	*/

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	/*
	* создаем структуру с полями нужного типа и отправляем эти поля по ссылке
	* в функцию mlx_get_data_ddr, которая их изменит (как то) и вернет адрес изображения
	*/

	int i = 0, j = 0;
	color = 0xFF1493;
	while (i < 50)
	{
		j=0;
		while (j < 100)
		{
			my_mlx_pixel_put(&img, i, j, color);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 100, 100);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 2, 1L<<0, close_esc, &vars);
	mlx_hook(vars.win, 17, 1L<<17, close_red_cross, &vars);
	mlx_hook(vars.win, 6, 1L<<6, mouse_hover, &vars);	
	mlx_loop(vars.mlx);

	/*=========================================
	** Для того чтобы выровнять байты относительно нашего окна(ЭТО НАДО ДЕЛАТЬ ВСЕГДА!)
	** надо взять следующую формулу:
	** int offset = (y * line_length + x * (bits_per_pixel / 8));
	*//*===========================================*/
}