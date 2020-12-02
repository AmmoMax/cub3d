/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:28:03 by amayor            #+#    #+#             */
/*   Updated: 2020/11/28 20:33:37 by amayor           ###   ########.fr       */
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
	ERR_DOUBLE_F_COLOR = -22,
	ERR_NOMAP = -23,
	ERR_TO_MANY_ARGS = -24,
	ERR_INV_FLAG = -25,
	ERR_MEMALLOC_CONVERTMAP = -26,
	ERR_MEMALLOC_MAP = -27,
	ERR_MAP_NOGMR_POS = -28,
	ERR_MAP_SURWALLS = -29,
	ERR_DOUBLE_PLR = -30,
	ERR_NO_RES = -31,
	ERR_NO_NTEX = -32,
	ERR_NO_STEX = -33,
	ERR_NO_WTEX = -34,
	ERR_NO_ETEX = -35,
	ERR_NO_SPRTEX = -36,
	ERR_NO_CLRF = -37,
	ERR_NO_CLRC = -38,
	ERR_INCPATH_TEX = -39,
	ERR_INCPATH_SPR = -40,
	ERR_INVFILE_CUB = -41,
	ERR_NO_MAP_INCONF = -42
}				t_error;

#endif
