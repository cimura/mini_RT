#include "renderer.h"

void	set_light_ratio(t_light_ratio *light, t_rgb rgb, double coefficient)
{
	light->red = rgb.red * coefficient;
	light->green = rgb.green * coefficient;
	light->blue = rgb.blue * coefficient;
}

t_light_ratio	add_light_ratio(t_light_ratio l1, t_light_ratio l2)
{
	t_light_ratio	result;

	result.red = l1.red + l2.red;
	if (result.red > 1.0)
		result.red = 1.0;
	result.green = l1.green + l2.green;
	if (result.green > 1.0)
		result.green = 1.0;
	result.blue = l1.blue + l2.blue;
	if (result.blue > 1.0)
		result.blue = 1.0;
	return (result);
}

t_light_ratio	multi_light_ratio(t_light_ratio l1, t_light_ratio l2)
{
	t_light_ratio	result;

	result.red = l1.red * l2.red;
	result.green = l1.green * l2.green;
	result.blue = l1.blue * l2.blue;
	return (result);
}

int	rgb_to_colorcode(t_light_ratio light)
{
	int	result;

	// result = red.value*red.R_r * pow(16, 4) + green.value*green.R_r * pow(16, 2) + blue.value*blue.R_r;
		result = (int)(light.red * 255) << 16  // 赤は上位16ビット
		   | (int)(light.green * 255) << 8  // 緑は中間8ビット
		   | (int)(light.blue * 255);  // 青は下位8ビット
	return (result);
}
