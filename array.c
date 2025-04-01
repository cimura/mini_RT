#include <stdio.h>
#include <stdlib.h>

void	array_init(double array[], int size, double value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		array[i] = value;
		i++;
	}
}

void	array_print(double array[], int size)
{
	int	i;

	printf("[");
	i = 0;
	while (i < size)
	{
		printf("%lf ", array[i]);
		i++;
	}
	printf("]");
}

#define ARRAY_SIZE 256

int	main(void)
{
	double	*pointer;
	double	array[ARRAY_SIZE];

	pointer = malloc(ARRAY_SIZE * sizeof(double));
	array_init(array, ARRAY_SIZE, -1);
	array[0] = 2;
	array_print(array, ARRAY_SIZE);
	free(pointer);
	return (0);
}
