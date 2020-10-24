/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 22:39:43 by amayor            #+#    #+#             */
/*   Updated: 2020/10/24 22:06:09 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/utils.h"
#include <fcntl.h>
#define ERROR 1
#define OK 0

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
	else if (ft_strchr(line, '1')) // TODO: более точное условие строки с картой
		return (map_handler(line, config));
	else if (line[0] == '\n' || line[0] == 0)
		return (OK);
	else
		return (OK);
}


int					main (int argc, char *argv[])
{
	int				fd;
	char			*line;
	m_config		config;
	m_config		*config_p;
	char			**map;
	int				len_map;

	line = NULL;
	config.floor = NULL;
	config.ceiling = NULL;
	config_p = malloc(sizeof(m_config));
	if (argc == 1)
	{
		ft_putendl_fd("Use: cub3d <path to map.cub>", 1);
		return (1);
	}
	fd = open(argv[1], O_RDONLY); // обработка ошибок открытия файла
	while (get_next_line(fd, &line)) // malloc line
	{
		// printf("config line = *%s*\n", line);
		if (line_handler(line, &config_p) != 0) // если обработчик строки вернул ошибку - возвращаем ошибку тут
		{
			printf("Error processing line: *%s*\n", line);
			printf("Map file not valid\n");
			return (1);
		}
		// free(line);
	}
	map = convert_map(&(config_p->map));
	len_map = ft_lstsize(config.map);
	if (map_validator(map, len_map) == 1)
		printf("***\nMap is NOT VALID!\n***\n\n");
	else
		printf("***\nMap is VALID!\n***\n\n");
	printf("resolution: x = %d, y = %d\n", config_p->x, config_p->y);
	printf("Path to NO texture = %s\n", config_p->no_texture);
	printf("Path to SO texture = %s\n", config_p->so_texture);
	printf("Path to WE texture = %s\n", config_p->we_texture);
	printf("Path to EA texture = %s\n", config_p->ea_texture);
	printf("Path to Sprite = %s\n", config_p->s_texture);
	printf("Color ceiling: red = %d, green = %d, blue = %d\n", config_p->ceiling->red, config_p->ceiling->green, config_p->ceiling->blue);
	printf("Color floor: red = %d, green = %d, blue = %d\n", config_p->floor->red, config_p->floor->green, config_p->floor->blue);
	free(config.ceiling);
	free(config.floor);
	return (0);
}
