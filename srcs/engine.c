/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:49:02 by amayor            #+#    #+#             */
/*   Updated: 2020/11/24 00:34:28 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

int				check_config(m_config *config)
{
	if (config->count_res == 0)
		return(ERR_NO_RES);
	else if (config->count_ntex == 0)
		return(ERR_NO_NTEX);
	else if (config->count_stex == 0)
		return(ERR_NO_STEX);
	else if (config->count_wtex == 0)
		return(ERR_NO_WTEX);
	else if (config->count_etex == 0)
		return(ERR_NO_ETEX);
	else if (config->count_sprtex == 0)
		return(ERR_NO_SPRTEX);
	else if (config->count_clrf == 0)
		return(ERR_NO_CLRF);
	else if (config->count_clrc == 0)
		return(ERR_NO_CLRC);
	else
		return (0);
}

static int		print_check_config(m_config *config)
{
	int			res;

	if ((res = check_config(config)) != 0)
	{
		print_err(res);
		return (res);
	}
	else
		return (0);
}

static int		clean_flat_map(m_config *config)
{
	cleanup_map(&config->map);
	clean_config_no_map(&config);
	return(ERR_MEMALLOC_CONVERTMAP);
}

int				start_cub3d(char *path, char *save_f)
{
	m_config	*config;
	int			len_map;
	int 		save_flag;

	if (save_f && ft_strncmp("--save", save_f, ft_strlen(save_f)) != 0)
		return(local_print_error(ERR_INV_FLAG));
	save_flag = 0;
	if (save_f)
		save_flag = 1;
	ft_putstr_fd("Start reading map file...\n", 1);
	if (!(config = read_config(path)))
		return (1);
	if (print_check_config(config) != 0)
		return (1);
	config->flat_map = convert_map(config->map, &config);
	if (!(config->flat_map))
		return(clean_flat_map(config));
	len_map = ft_lstsize(config->map);
	if (map_validator(config->flat_map, len_map) != 0)
		return (ERR_INVMAP);
	if (check_path_tex(config) != 0)
		return (1);
	g_engine(config, save_flag);
	return (0);
}
