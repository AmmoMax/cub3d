#include <stdio.h>
#include "utils.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	if (!s)
		return (0);
	while (*s)
	{
		len += 1;
		s++;
	}
	return (len);
}

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;
	size_t			i;

	i = 0;
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (i < n)
	{
		if (us1[i] != us2[i])
		{
			return (us1[i] - us2[i]);
		}
		i += 1;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	int		result_cmp;

	little_len = ft_strlen(little);
	if (!little_len)
		return ((char*)big);
	while (len >= little_len && *big)
	{
		result_cmp = ft_memcmp(big, little, little_len);
		if (result_cmp == 0)
		{
			return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}



/*
* Здесь находится валидатор и парсер строки текстуры.
* Валидные строки текстуры выглядят так:
* NO ./path_to_the_north_texture
* SO ./path_to_the_south_texture
* WE ./path_to_the_west_texture
* EA ./path_to_the_east_texture
* Надо определять какая строка и сохранять ее в соответствующую переменную в общей структуре конфига.
*
*
*/

/*
* Валидирует строку текстуры, считанную из файла с картой.
* Обрабатывает 4 вида текстуры.
* Возвращает 0 если текстура валидна, 1 если невалидна.
*
* Строка состоит из двух символов идентификатора - NO, SO, WE, EA и пути к файлу с текстурой.
* 1. Ищем в строке определенный идентификатор. Если нашли - передаем строку для парсинга пути. Если не нашли - возвращаем ошибку.
*/


/*
* Принимает строку для парсинга пути к текстуре и конфиг для сохранения.
* Пример строки: EA ./path_to_the_east_texture
*
*/
int tex_parser(char *line, char flag, m_config **config)
{
	size_t	i;
	char	*tmp_line;

	i = 0;
	while (line[i] == ' ')
		i++;
	if(flag == 'N')
		(*config)->no_texture = line + i;
	else if(flag = 'S')
		(*config)->so_texture = line + i;
	else if(flag = 'W')
		(*config)->we_texture = line + i;
	else if(flag = 'E')
		(*config)->ea_texture = line + i;
	return (0);
}

int	tex_validator(char *line, m_config **config)
{
	size_t	i;
	char	*res;

	i = 0;
	while (line[i])
	{
		if(res = ft_strnstr(line, "NO", ft_strlen(line)))
			return (tex_parser(res + 2, 'N', config));
		else if(res = ft_strnstr(line, "SO", ft_strlen(line)))
			return (tex_parser(res + 2, 'S', config));
		else if(res = ft_strnstr(line, "WE", ft_strlen(line)))
			return (tex_parser(res + 2, 'W', config));
		else if(res = ft_strnstr(line, "EA", ft_strlen(line)))
			return (tex_parser(res + 2, 'E', config));
		else
			return (1);
	}

}


int main()
{
	char		*texture;
	m_config	config;
	m_config	*p_config;

	p_config = &config;
	texture = "NO ./path_to_the_north_texture";
	if (tex_validator(texture, &p_config) == 0)
		printf("Texture is valid\n");
	printf("Path to NO texture = %s\n", config.no_texture);
	
	return (0);
}
