#include "libft.h"


char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s)
			s++;
		else
			return (NULL);
	}
	return (char *)s;
}


int main()
{
	char *str;

	str = "1100000000W0000011010100100011";
	ft_strchr(str, '1');
}
