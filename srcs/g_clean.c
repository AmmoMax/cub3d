/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_clean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:58:24 by amayor            #+#    #+#             */
/*   Updated: 2020/11/21 14:20:49 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void	cleanup_xpm(t_xpm **p_tex, t_world *world)
{
	t_xpm	*tex;

	tex = *p_tex;
	if(tex)
	{
		mlx_destroy_image(world->win->mlx, tex->img);
		free(tex->tex_pix);
		tex->tex_pix = NULL;
		free(*p_tex);
		*p_tex = NULL;
	}
}

void		cleanup_all_tex(t_tex **p_textures, t_world *world)
{
	t_tex	*textures;

	textures = *p_textures;
	if (textures->n_tex)
	{
		cleanup_xpm(&textures->n_tex, world);
		// free(textures->n_tex);
	}
	// textures->n_tex = NULL;
	if (textures->s_tex)
	{
		cleanup_xpm(&textures->s_tex, world);
		// free(textures->s_tex);
	}
	// textures->s_tex = NULL;
	if (textures->e_tex)
	{
		cleanup_xpm(&textures->e_tex, world);
		// free(textures->e_tex);
	}
	// textures->e_tex = NULL;
	if (textures->w_tex)
	{
		cleanup_xpm(&textures->w_tex, world);
		// free(textures->w_tex);
	}
	// textures->w_tex = NULL;
	if (textures->sprite_tex)
	{
		cleanup_xpm(&textures->sprite_tex, world);
		// free(textures->sprite_tex);
	}
	// textures->sprite_tex = NULL;
	free(*p_textures);
	*p_textures = NULL;
}

void			cleanup_sprites(t_sprite **sprites_head)
{
	t_sprite	*addr_next;
	t_sprite	*counter;

	counter = *sprites_head;
	while (counter)
	{
		addr_next = counter->next;		
		counter->next = NULL;
		free(counter);
		counter = addr_next;
	}
	*sprites_head = NULL;
}

void		cleanup_all_world(t_world **p_world)
{
	t_world	*world;

	world = *p_world;
	clean_config_all(&world->config);
	cleanup_all_tex(&world->t, world);
	cleanup_sprites(&world->sprites);
	free(world->dist_wall);
	mlx_destroy_image(world->win->mlx, world->win->img);
	mlx_destroy_window(world->win->mlx, world->win->win);
	free(world->win);
	world->win = NULL;
	free(*p_world);
	*p_world = NULL;
}

void		cleanup_win(t_win **win)
{
	mlx_destroy_image((*win)->mlx, (*win)->img);
	mlx_destroy_window((*win)->mlx, (*win)->win);
	free(*win);
	*win = NULL;
}

void		cleanup_save_sprite_pos(t_world **world)
{
	cleanup_sprites(&(*world)->sprites);
	cleanup_all_tex(&(*world)->t, *world);
	cleanup_win(&(*world)->win);
	clean_config_all(&(*world)->config);
	free((*world)->dist_wall);
	free(*world);
}