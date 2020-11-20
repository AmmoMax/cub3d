/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:29:30 by amayor            #+#    #+#             */
/*   Updated: 2020/11/20 22:05:15 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

int			*strcpy_int(int *dst, int *src)
{
	size_t			i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	get_textures(t_world *world, t_xpm *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(world->win->mlx, path, &texture->width, &texture->height);
	texture->tex_pix = (int *)mlx_get_data_addr(texture->img, &texture->bbp, &texture->line_length, &texture->endian);
}

/*
** Загружает текстуры в общую структуру мира
*/
int			load_textures(t_world **world)
{
	size_t	i;
	t_xpm	*tex;
	t_tex	*all_t;
	char *path;

	i = 0;
	if (!(tex = (t_xpm*)malloc(sizeof(t_xpm))))
		return (ERR_MEMALLOC);
	if (!(all_t = (t_tex *)malloc(sizeof(t_tex))))
		return (ERR_MEMALLOC);
	path = (*world)->config->ea_texture;
	tex->img = mlx_xpm_file_to_image((*world)->win->mlx, path, &tex->width, &tex->height);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bbp, &tex->line_length, &tex->endian);
	tex->tex_pix = (int *)malloc(sizeof(int) * (tex->height * tex->width + 1));
	strcpy_int(tex->tex_pix, (int *)tex->addr);
	(*world)->t = all_t;
	(*world)->t->e_tex = tex;
	return (0);
}

static t_xpm	*load_one_tex(t_world *world, char *path)
{
	t_xpm	*tex;

	if (!(tex = (t_xpm*)malloc(sizeof(t_xpm))))
		return (NULL);
	tex->img = mlx_xpm_file_to_image(world->win->mlx, path, &tex->width, &tex->height);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bbp, &tex->line_length, &tex->endian);
	tex->tex_pix = (int *)malloc(sizeof(int) * (tex->height * tex->width + 1));
	strcpy_int(tex->tex_pix, (int *)tex->addr);
	return (tex);
}

int			load_textures_v2(t_world **world)
{
	t_tex	*all_t;

	if (!(all_t = (t_tex *)malloc(sizeof(t_tex))))
	{
		clean_config_all(&(*world)->config);
		cleanup_win(&(*world)->win);
		free((*world)->dist_wall);
		free(*world);
		return (ERR_MEMALLOC);
	}
	(*world)->t = all_t;
	(*world)->t->e_tex = load_one_tex(*world, (*world)->config->ea_texture); // возвращает указатель на загруженную текстуру
	(*world)->t->s_tex = load_one_tex(*world, (*world)->config->so_texture); // возвращает указатель на загруженную текстуру
	(*world)->t->n_tex = load_one_tex(*world, (*world)->config->no_texture); // возвращает указатель на загруженную текстуру
	(*world)->t->w_tex = load_one_tex(*world, (*world)->config->we_texture); // возвращает указатель на загруженную текстуру
	return (0);
}
