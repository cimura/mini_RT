#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*f(void *ptr)
{
	strcpy(ptr, "world");
	return (ptr);
}

int	main() {
	char	*str = malloc(6);
	strcpy(str, "hello");

	printf("str: %s\n", str);
	void	*ret = f(str);
	printf("str: %s\n", ret);
}
