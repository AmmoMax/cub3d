#include <stdio.h>


int main()
{
	char str[] = "abc";

	printf("*%s*\n", str);

	str[3] = ' ';
	// str[4] = '\0';
	str[5] = 'd';

	printf("*%s*\n", str);

}
