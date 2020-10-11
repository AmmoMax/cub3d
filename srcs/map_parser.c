/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 22:39:43 by amayor            #+#    #+#             */
/*   Updated: 2020/10/08 22:29:19 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/utils.h"
#include <fcntl.h>
#define ERROR 1
#define OK 0

#include <stdio.h>


/*
* Предполагается что функция будет обрабатывать строку из файла и для каждой опции вызывать нужный суб-обработчик
*/
int			line_handler(char *line, m_config **config)
{
	size_t	len;

	len = ft_strlen(line);
	if (ft_strchr(line, 'R'))
		return (res_handler(line, config));
	else if (ft_strnstr(line, "NO", len) || ft_strnstr(line, "SO", len) ||
			 ft_strnstr(line, "WE", len) || ft_strnstr(line, "EA", len))
		return (texture_handler(line, config));
	else if (ft_strchr(line, 'S'))
		return (sprite_handler(line, config));
	else if (ft_strchr(line, 'F')|| ft_strchr(line, 'C'))
		return(color_handler(line, config));
	else
		return (OK);
	// else if (*line == 1)
	// 	map_handler(line);
}

/*
* Должен сохранять ТОЛЬКО карту в двумерный массив.
* Пока непонятно как считать длину самой длинной строчки в карте, чтобы по ней выделять память.
*/
// void		make_map(t_list **head, int size) 
// {
// 	char	**map;
// 	t_list	*tmp;
// 	int		i;

// 	i = -1;
// 	if(!(map = (char **)ft_calloc(size + 1, sizeof(char *))))
// 		return ;
// 	tmp = *head;
// 	while (tmp)
// 	{
// 			map[++i] = tmp->content; // надо выделять память под каждую строку?
// 			tmp = tmp->next;
// 	}
// }

int					main (int argc, char *argv[])
{
	int				fd;
	char			*line;
	// t_list		*head;
	m_config		config;
	m_config		*config_p;

	line = NULL;
	
	config_p = &config;
	if (argc == 1)
	{
		ft_putendl_fd("Use: cub3d <path to map.cub>", 1);
		return (1);
	}
	fd = open(argv[1], O_RDONLY); // обработка ошибок открытия файла
	while (get_next_line(fd, &line)) // malloc line
	{
		if (line_handler(line, &config_p) != 0) // если обработчик строки вернул ошибку - возвращаем ошибку тут
		{
			printf("Error processing line: %s\n", line);
			printf("Map file not valid\n");
			// return (1);
		}
	}
	printf("resolution: x = %d, y = %d\n", config_p->x, config_p->y);
	printf("Path to NO texture = %s\n", config.no_texture);
	printf("Path to SO texture = %s\n", config.so_texture);
	printf("Path to WE texture = %s\n", config.we_texture);
	printf("Path to EA texture = %s\n", config.ea_texture);
	printf("Path to Sprite = %s\n", config.s_texture);
	printf("Color ceiling: red = %d, green = %d, blue = %d\n", config.ceiling->red, config.ceiling->green, config.ceiling->blue);
	printf("Color floor: red = %d, green = %d, blue = %d\n", config.floor->red, config.floor->green, config.floor->blue);
	free(config.ceiling);
	free(config.floor);
	return (0);
}
