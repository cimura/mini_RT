#include <stdio.h>

double	ft_atod(char *nptr);

int	main(void)
{
	double	a;
	char	*str;

	a = 12123456789123.;
	printf("%lf\n", a);
	str = "   1111111111111111111111.012345";
	printf("str = %s\n", str);
	//a = ft_atod(str);
	//printf("double = %lf\n", a);
	return (0);
}
