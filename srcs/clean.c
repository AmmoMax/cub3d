/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:27:15 by amayor            #+#    #+#             */
/*   Updated: 2020/10/28 22:52:30 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

void			cleanup_map(m_config *config)
{
	t_list	*head;
	t_list	*addr_next;

	head = config->map;
	while (head)
	{
		addr_next = head->next;
		head->next = NULL;
		free(head);
		head = addr_next;
	}
	return ;
}

void			cleanup_flat_map(char **map)
{
	free(map[0];
	free(map);
	map = NULL;
	return ;
}