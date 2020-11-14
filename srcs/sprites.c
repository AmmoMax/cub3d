/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 12:22:56 by amayor            #+#    #+#             */
/*   Updated: 2020/11/14 12:59:44 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static t_sprite		*new_sprite(float x, float y)
{
	t_sprite		*new;

	if(!(new = (t_sprite *)malloc(sizeof(t_sprite))))
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

int					save_sprites_pos(t_world **world)
{
	char			**map;
	t_sprite		*sprite;
	size_t			i;
	size_t			j;

	map = (*world)->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				// сохранить координаты в очередной элемент односвязного списка спрайтов
				if(!(sprite = new_sprite(j * SCALE, i * SCALE)))
					return (ERR_GET_SPRITES);
				lst_add_back(&(*world)->sprites, sprite);
			}
			j++;
		}
		i++;
	}
	return (0);
}
