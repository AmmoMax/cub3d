/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:00:47 by amayor            #+#    #+#             */
/*   Updated: 2020/11/28 18:34:01 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/general.h"

void		set_texture(t_config **config, char *str,
						char *line, char flag)
{
	if (flag == 'N')
	{
		(*config)->no_texture = ft_strcpy(str, line);
		(*config)->count_ntex = 1;
	}
	else if (flag == 'S')
	{
		(*config)->so_texture = ft_strcpy(str, line);
		(*config)->count_stex = 1;
	}
	else if (flag == 'W')
	{
		(*config)->we_texture = ft_strcpy(str, line);
		(*config)->count_wtex = 1;
	}
	else if (flag == 'E')
	{
		(*config)->ea_texture = ft_strcpy(str, line);
		(*config)->count_etex = 1;
	}
}

static int	comma_counter(char *line)
{
	size_t	i;
	size_t	comma_count;

	i = -1;
	comma_count = 0;
	while (line[++i])
	{
		if (line[i] == ',')
			comma_count++;
	}
	return (comma_count == 2 ? 0 : ERR_INVLINE_COLOR);
}

/*
** Валидирует строку с кодом цвета в RGB
** Пример валидной строки: "F 220,100,0";
*/

int			color_validator(char *line)
{
	size_t	i;
	size_t	num_cnt;
	char	*tmp;
	size_t	f_color;

	i = -1;
	num_cnt = 0;
	tmp = line;
	while (line[++i])
	{
		if ((line[i] == 'C' || line[i] == 'F') && line[i + 1] == ' ')
			f_color = 1;
		else if (line[i] == ' ' || line[i] == ',' ||
				(ft_isdigit(line[i]) && ft_isdigit(line[i - 1])))
			;
		else if (ft_isdigit(line[i]) && !(ft_isdigit(line[i - 1])))
		{
			if (ft_atoi(tmp + i) > 255 || ft_atoi(tmp + i) < 0 || f_color != 1)
				return (ERR_INVLINE_COLOR);
			num_cnt++;
		}
		else
			return (ERR_INVLINE_COLOR);
	}
	return (num_cnt == 3 ? comma_counter(line) : ERR_INVLINE_COLOR);
}

int			max_len_line(t_list *head)
{
	size_t	max_len;
	size_t	len;

	max_len = 0;
	len = 0;
	while (head)
	{
		len = ft_strlen(head->content);
		if (len > max_len)
			max_len = len;
		head = head->next;
	}
	return (max_len);
}

int			check_player(int flag)
{
	if (flag > 1)
	{
		print_err(ERR_DOUBLE_PLR);
		return (1);
	}
	else if (flag < 1)
	{
		print_err(ERR_MAP_NOGMR_POS);
		return (1);
	}
	else
		return (0);
}
