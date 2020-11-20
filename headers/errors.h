/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:28:03 by amayor            #+#    #+#             */
/*   Updated: 2020/11/20 16:01:01 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum	e_errors
{
	ERR_OK = 0,
	ERR_PARSE = -1,
	ERR_MEMALLOC = -2,
	ERR_INVMAP = -3, 
	ERR_GET_SPRITES = -4,
	ERR_PARSE_TEX = -5,
	ERR_PARSE_SPRITE = -6,
	ERR_INVSPRITE = -7, 
	ERR_INVCOLOR = -8
}				t_error;

#endif
