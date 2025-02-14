#include "draw.h"

__int32_t	map(t_color red, t_color green, t_color blue)
{
	__int32_t	result;

	result = red.value*red.R_r * pow(16, 4) + green.value*green.R_r * pow(16, 2) + blue.value*blue.R_r;
	return (result);
}