/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:28:03 by amayor            #+#    #+#             */
/*   Updated: 2020/11/14 12:41:07 by amayor           ###   ########.fr       */
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
	ERR_GET_SPRITES = -4
}				t_error;

#endif
