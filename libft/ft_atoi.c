/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:19:03 by amayor            #+#    #+#             */
/*   Updated: 2020/11/28 15:24:02 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(char const *str)
{
	int				n;
	unsigned long	r;

	n = 1;
	r = 0;
	while (*str == '\t' || *str == '\v' ||
			*str == '\f' || *str == '\n' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			n = -1;
		str++;
	}
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		if ((r * 10 + (*str - '0')) < r)
			return ((n > 0) ? -1 : 0);
		r = r * 10 + (*str - '0');
		str++;
	}
	return ((int)(r * n));
}
