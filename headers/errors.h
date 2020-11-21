/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:28:03 by amayor            #+#    #+#             */
/*   Updated: 2020/11/21 18:38:20 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum	e_errors
{
	ERR_OK = 0,
	ERR_PARSE_CFILE = -1,
	ERR_MEMALLOC = -2,
	ERR_INVMAP = -3, 
	ERR_GET_SPRITES = -4,
	ERR_PARSE_TEX = -5,
	ERR_PARSE_SPRITE = -6,
	ERR_INVSPRITE = -7, 
	ERR_INVCOLOR = -8,
	ERR_OFILE = -9,
	ERR_INVLINE_CONF = -10,
	ERR_DOUBLE_RES = -11,
	ERR_INVRES = -12,
}				t_error;

#endif
