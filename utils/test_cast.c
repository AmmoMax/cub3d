#include <stdio.h>
#include <stdlib.h>

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c_s1;
	unsigned char	*c_s2;
	size_t			i;

	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	i = n;
	if (!c_s1 || !c_s2 || i == 0)
		return (0);
	while (i-- > 0)
	{
		if (*c_s1 == *c_s2)
		{
			c_s1++;
			c_s2++;
		}
		else
			return (*c_s1 - *c_s2);
	}
	return (0);
}

int main ()
{
	char *s1 = "\xff\0\0\xaa\0\xde\xffMACOSX\xff";
	char *s2 = "\xff\0\0\xaa\0\xde\x00MBS";
	size_t size = 9;	
	printf("custom = %d\n", ft_memcmp(s1, s2, size));
	printf("original = %d\n", memcmp(s1, s2, size));

	return (0);
}