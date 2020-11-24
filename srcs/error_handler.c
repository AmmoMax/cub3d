/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:25:38 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 23:48:42 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

static void	print_err_4(int err_type)
{
	if (err_type == ERR_INVMAP)
		ft_putstr_fd("Error : \nInvalid map\n", 1);
	else if (err_type == ERR_INVFILE_CUB)
		ft_putstr_fd("Error :\nInvalid file. The file extension must be .cub\n", 1);

}

static void	print_err_3(int err_type)
{
	if (err_type == ERR_DOUBLE_PLR)
		ft_putstr_fd("Error :\nMultiple starting positions\n", 1);
	else if (err_type == ERR_NO_RES)
		ft_putstr_fd("Error :\nNo resolution specified\n", 1);
	else if (err_type == ERR_NO_NTEX)
		ft_putstr_fd("Error :\nThe north texture is not defined\n", 1);
	else if (err_type == ERR_NO_STEX)
		ft_putstr_fd("Error :\nThe south texture is not defined\n", 1);
	else if (err_type == ERR_NO_WTEX)
		ft_putstr_fd("Error :\nThe west texture is not defined\n", 1);
	else if (err_type == ERR_NO_ETEX)
		ft_putstr_fd("Error :\nThe east texture is not defined\n", 1);
	else if (err_type == ERR_NO_SPRTEX)
		ft_putstr_fd("Error :\nThe sprite texture is not defined\n", 1);
	else if (err_type == ERR_NO_CLRF)
		ft_putstr_fd("Error :\nThe floor color is not defined\n", 1);
	else if (err_type == ERR_NO_CLRC)
		ft_putstr_fd("Error :\nThe ceiling color is not defined\n", 1);
	else if (err_type == ERR_INCPATH_TEX)
		ft_putstr_fd("Error :\nIncorrect path to texture\n", 1);
	else if (err_type == ERR_INCPATH_SPR)
		ft_putstr_fd("Error :\nIncorrect path to sprite\n", 1);
	else
		print_err_4(err_type);
}

static void	print_err_2(int err_type)
{
	if (err_type == ERR_INVLINE_COLOR)
		ft_putstr_fd("Error :\nInvalid line in file - color path\n", 1);
	else if (err_type == ERR_MEMALLOC_COLORPARSER)
		ft_putstr_fd("Error :\nMalloc fail (color parser)\n", 1);
	else if (err_type == ERR_DOUBLE_C_COLOR)
		ft_putstr_fd("Error :\nColor path for ceiling specified twice\n", 1);
	else if (err_type == ERR_DOUBLE_F_COLOR)
		ft_putstr_fd("Error :\nColor path for floor specified twice\n", 1);
	else if (err_type == ERR_NOMAP)
		ft_putstr_fd("Error \n No map file. Run like this - ./cub3D map.cub\n", 1);
	else if (err_type == ERR_TO_MANY_ARGS)
		ft_putstr_fd("Error :\nToo many arguments. Run like this - ./cub3D map.cub\n", 1);
	else if (err_type == ERR_INV_FLAG)
		ft_putstr_fd("Error :\nInvalid argument. Run like this - ./cub3D map.cub --save\n", 1);
	else if (err_type == ERR_MEMALLOC_CONVERTMAP)
		ft_putstr_fd("Error :\nMalloc fail (convert map)\n", 1);
	else if (err_type == ERR_MEMALLOC_MAP)
		ft_putstr_fd("Error :\nMalloc fail (map parser)\n", 1);
	else if (err_type == ERR_MAP_NOGMR_POS)
		ft_putstr_fd("Error :\nNo starting player position\n", 1);
	else if (err_type == ERR_MAP_SURWALLS)
		ft_putstr_fd("Error :\nMap isn't surrounded by walls\n", 1);
	else print_err_3(err_type);

}

void	print_err(int err_type)
{
	if (err_type == ERR_OFILE)
		ft_putstr_fd("Error :\nCouldn't open file (FD)\n", 1);
	else if (err_type == ERR_PARSE_CFILE)
		ft_putstr_fd("Error :\nCouldn't parse file (GNL)\n", 1);
	else if (err_type == ERR_INVLINE_CONF)
		ft_putstr_fd("Error :\nInvalid line in file\n", 1);
	else if (err_type == ERR_DOUBLE_RES)
		ft_putstr_fd("Error :\nResolution specified twice\n", 1);
	else if (err_type == ERR_INVRES)
		ft_putstr_fd("Error :\nInvalid resolution\n", 1);
	else if (err_type == ERR_MEMALLOC_TEXPARSER)
		ft_putstr_fd("Error :\nMalloc fail (texture parser)\n", 1);
	else if (err_type == ERR_INVLINE_TEX)
		ft_putstr_fd("Error :\nInvalid line in file - texture path\n", 1);
	else if (err_type == ERR_DOUBLE_TEX)
		ft_putstr_fd("Error :\nTexture path specified twice\n", 1);
	else if (err_type == ERR_INVLINE_SPRITE)
		ft_putstr_fd("Error :\nInvalid line in file - sprite path\n", 1);
	else if (err_type == ERR_MEMALLOC_SPRTPARSER)
		ft_putstr_fd("Error :\nMalloc fail (sprite parser)\n", 1);
	else if (err_type == ERR_DOUBLE_SPRITE)
		ft_putstr_fd("Error :\nSprite path specified twice\n", 1);
	else
		print_err_2(err_type);
}
