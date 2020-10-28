#include <stdio.h>

typedef enum	e_errors
{
	ERR_OK = 0,
	ERR_PARSE = -1

}				t_errors;

void test_err(int errcode)
{
	errcode == ERR_OK ? printf("All ok\n") : 0;
	errcode == ERR_PARSE ? printf("Parsig file error\n") : 0;
	return ;
}

int main ()
{	
	int errcode = 2;
	char test = "1234";

	test_err(errcode);
	free(&test);
	return (0);
}