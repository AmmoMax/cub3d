/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:29:30 by amayor            #+#    #+#             */
/*   Updated: 2020/11/26 22:26:08 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

int				*strcpy_int(int *dst, int *src)
{
	size_t		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void			get_textures(t_world *world, t_xpm *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(world->win->mlx,
			path, &texture->width, &texture->height);
	texture->tex_pix = (int *)mlx_get_data_addr(texture->img, &texture->bbp,
			&texture->line_length, &texture->endian);
}

static t_xpm	*load_one_tex(t_world *world, char *path)
{
	t_xpm		*tex;

	if (!(tex = (t_xpm*)malloc(sizeof(t_xpm))))
		return (NULL);
	tex->img = mlx_xpm_file_to_image(world->win->mlx,
				path, &tex->width, &tex->height);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bbp,
			&tex->line_length, &tex->endian);
	tex->tex_pix = (int *)malloc(sizeof(int) * (tex->height * tex->width + 1));
	strcpy_int(tex->tex_pix, (int *)tex->addr);
	return (tex);
}

static void		local_clean(t_world **w)
{
	clean_config_all(&(*w)->config);
	cleanup_win(&(*w)->win);
	free((*w)->dist_wall);
	free(*w);
}

int				load_textures_v2(t_world **w)
{
	t_tex		*all_t;

	if (!(all_t = (t_tex *)ft_calloc(1, sizeof(t_tex))))
	{
		local_clean(w);
		return (ERR_MEMALLOC);
	}
	(*w)->t = all_t;
	(*w)->t->e_tex = load_one_tex(*w, (*w)->config->ea_texture);
	(*w)->t->s_tex = load_one_tex(*w, (*w)->config->so_texture);
	(*w)->t->n_tex = load_one_tex(*w, (*w)->config->no_texture);
	(*w)->t->w_tex = load_one_tex(*w, (*w)->config->we_texture);
	if (!(*w)->t->e_tex || !(*w)->t->s_tex || !(*w)->t->n_tex
						|| !(*w)->t->w_tex)
	{
		cleanup_all_tex(&(*w)->t, *w);
		local_clean(w);
		return (ERR_MEMALLOC);
	}
	return (0);
}
