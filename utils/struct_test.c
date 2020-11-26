#include <stdio.h>
#include <stdlib.h>

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;


int main()
{
	t_color	*color_p;
	color_p = (t_color*)(malloc(sizeof(t_color)));
	color_p->red = -1;
	color_p->green = -1;
	color_p->blue = -1;
	printf("Color: red = %d, green = %d, blue = %d", color_p->red, color_p->green, color_p->blue);
	free(color_p);
	return (0);
}
