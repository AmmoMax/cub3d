/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:27:15 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 23:41:55 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

void			cleanup_map(t_list **map_head)
{
	t_list	*addr_next;
	t_list	*counter;

	counter = *map_head;
	while (counter)
	{
		addr_next = counter->next;
		free(counter->content);
		counter->next = NULL;
		free(counter);
		counter = addr_next;
	}
	*map_head = NULL;
}

void			clean_config_all(m_config **p_config)
{
	m_config	*config;
	config = *p_config;
	free(config->no_texture);
	config->no_texture = NULL;
	free(config->so_texture);
	config->so_texture = NULL;
	free(config->we_texture);
	config->we_texture = NULL;
	free(config->ea_texture);
	config->ea_texture = NULL;
	free(config->s_texture);
	config->s_texture = NULL;
	free(config->floor);
	config->floor = NULL;
	free(config->ceiling);
	config->ceiling = NULL;
	cleanup_map(&config->map);
	cleanup_flat_map(config->flat_map);
	free(*p_config);
	p_config = NULL;
}

void			clean_config_no_map(m_config **p_config)
{
	m_config	*config;
	config = *p_config;
	free(config->no_texture);
	config->no_texture = NULL;
	free(config->so_texture);
	config->so_texture = NULL;
	free(config->we_texture);
	config->we_texture = NULL;
	free(config->ea_texture);
	config->ea_texture = NULL;
	free(config->s_texture);
	config->s_texture = NULL;
	free(config->floor);
	config->floor = NULL;
	free(config->ceiling);
	config->ceiling = NULL;
	free(*p_config);
	p_config = NULL;
}

void			cleanup_flat_map(char **map)
{
	free(map[0]);
	map[0] = NULL;
	free(map);
	map = NULL;
	return ;
}
