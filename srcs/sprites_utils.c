/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 12:22:56 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 14:04:46 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static t_sprite		*new_sprite(float x, float y)
{
	t_sprite		*new;

	if (!(new = (t_sprite *)malloc(sizeof(t_sprite))))
		return (NULL);
	new->next = NULL;
	new->x = x;
	new->y = y;
	return (new);
}

static void			lst_add_back(t_sprite **head, t_sprite *new)
{
	t_sprite		*start;

	start = *head;
	if (start)
	{
		while(start->next)
			start = start->next;
		start->next = new;
		new->next = NULL;
	}
	else
		*head = new;
}

static void		local_clean(t_world **w)
{
	cleanup_all_tex(&(*w)->t, *w);
	cleanup_win(&(*w)->win);
	clean_config_all(&(*w)->config);
	free((*w)->dist_wall);
	free(*w);
}

int					save_sprites_pos(t_world **world)
{
	char			**map;
	t_sprite		*sprite;
	size_t			i;
	size_t			j;

	map = (*world)->map;
	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				if(!(sprite = new_sprite(j * SCALE + (SCALE / 2), i * SCALE + (SCALE / 2))))
				{
					cleanup_save_sprite_pos(world);
					return (ERR_MEMALLOC);
				}
				lst_add_back(&(*world)->sprites, sprite);
			}
			j++;
		}
	}
	return (0);
}

/*
** Загружает спрайт в общую структуру мира
*/
int				load_sprite(t_world **world)
{
	t_xpm		*tex;

	if (!(tex = (t_xpm*)malloc(sizeof(t_xpm))))
	{
		local_clean(world);
		return (ERR_MEMALLOC);
	}
	tex->img = mlx_xpm_file_to_image((*world)->win->mlx, (*world)->config->s_texture, &tex->width, &tex->height);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bbp, &tex->line_length, &tex->endian);
	tex->tex_pix = (int *)ft_calloc(1, sizeof(int) * (tex->height * tex->width + 1));
	if(!tex->tex_pix)
	{
		mlx_destroy_image((*world)->win->mlx, tex->img);
		free(tex);
		local_clean(world);
		return (ERR_MEMALLOC);
	}
	strcpy_int(tex->tex_pix, (int *)tex->addr);
	(*world)->t->sprite_tex = tex;
	return (save_sprites_pos(world));
}
