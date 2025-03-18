#include "utils.h"

void	swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

// double型の変数を範囲内に落とし込む関数 (min <= max)
void	double_compressor(double *d, double min, double max)
{
	if (*d < min)
		*d = min;
	if (*d > max)
		*d = max;
}

void	free_double_pointer(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i] != NULL)
	{
		free(pointer[i]);
		pointer[i] = NULL;
		i++;
	}
	free(pointer);
}
