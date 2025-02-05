#include "draw.h"

__int32_t	map(double R_d)
{
	__int32_t	result;
	int	red;
	int green;
	int	blue;

	red = 255 * R_d;
	green = 255 * R_d;
	blue = 255 * R_d;

	result = red * pow(16, 4) + green * pow(16, 2) + blue;
	return (result);
}