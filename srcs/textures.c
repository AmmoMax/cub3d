/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:29:30 by amayor            #+#    #+#             */
/*   Updated: 2020/11/12 20:04:32 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

void	get_textures(t_world *world, t_xpm *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(world->win->mlx, path, &texture->width, &texture->height);
	texture->tex_pix = (int *)mlx_get_data_addr(texture->img, &texture->bbp, &texture->line_length, &texture->endian);
}

/*
** Загружает текстуры в общую структуру мира
** 
** 
*/
int			load_textures(t_world **world)
{
	size_t	i;
	t_xpm	*tex;
	t_tex	*all_t;
	char *path;

	i = 0;
	if (!(tex = (t_xpm*)malloc(sizeof(t_xpm))))
		return (1); // обработать ошибку при неудачном выделении памяти
	all_t = (t_tex *)malloc(sizeof(t_tex));
	// get_textures((*world), tex, (*world)->config->ea_texture);
	path = (*world)->config->ea_texture;
	tex->img = mlx_xpm_file_to_image((*world)->win->mlx, path, &tex->width, &tex->height);
	// tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bbp, &tex->line_length, &tex->endian);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bbp, &tex->line_length, &tex->endian);
	tex->tex_pix = (int *)malloc(sizeof(int) * (tex->height * tex->width + 1));
	while(tex->addr[i])
	{
		tex->tex_pix[i] = tex->addr[i];
		i++;
	}
	(*world)->t = all_t;
	(*world)->t->e_tex = tex;
	return (0);
}