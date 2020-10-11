#include <stdio.h>
#include <stdlib.h>

typedef struct	color_t
{
	int			red;
	int			green;
	int			blue;
}				color;


int main()
{
	color	*color_p;
	color_p = (color*)(malloc(sizeof(color)));
	color_p->red = -1;
	color_p->green = -1;
	color_p->blue = -1;
	printf("Color: red = %d, green = %d, blue = %d", color_p->red, color_p->green, color_p->blue);
	free(color_p);
	return (0);
}