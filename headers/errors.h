/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:28:03 by amayor            #+#    #+#             */
/*   Updated: 2020/11/21 23:22:19 by amayor           ###   ########.fr       */
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
	ERR_MEMALLOC_TEXPARSER = -13,
	ERR_INVLINE_TEX = -14, 
	ERR_DOUBLE_TEX = -15,
	ERR_MEMALLOC_SPRTPARSER = -16,
	ERR_INVLINE_SPRITE = -17,
	ERR_DOUBLE_SPRITE = -18,
	ERR_INVLINE_COLOR = -19,
	ERR_MEMALLOC_COLORPARSER = -20,
	ERR_DOUBLE_C_COLOR = -21,
	ERR_DOUBLE_F_COLOR = -22
}				t_error;

#endif
