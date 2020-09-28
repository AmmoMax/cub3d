#include <stdio.h>
#include "../headers/libft.h"
#include <fcntl.h>

static int    parse_line(char *str)
{
  int      x;
  int		flag_pl;

  x = 0;
  flag_pl = 0;
  while (str[x] != '\0')
  {
    if (str[x] == 'N' || str[x] == 'S' || str[x] == 'W' || str[x] == 'E')
	{
		printf("call init_player()\n");
		flag_pl = 1;
		// return (0);
	}
    //   init_player(str[x], x, y, all);
    else if (str[x] == '2')
	{
		printf("add map sprites in all - [%d]\n", x);
		// return (0);
	}
    //   all->map.sprites++;
    else if (str[x] != '0' && str[x] != '1' && str[x] != ' ')
	{
		printf("str[x] = %d call exit_cub()\n", str[x]);
		return (1);
	}
    //   exit_cub("Error : Invalid symbols in the map", all);
    x++;
  }
  return ((flag_pl == 1) ? 0 : 1);
}

int main()
{
	int fd;
	char *line;

	fd = open("../maps/clean_map.cub", O_RDONLY); // обработка ошибок открытия файла
	while (get_next_line(fd, &line)) // malloc line
	{
		printf("line from gnl = %s\n", line);
		// printf("parse_line code = %d\n",parse_line(line));
		parse_line(line);
	}
	close(fd);
	printf("END!\n");

	return (0);
}