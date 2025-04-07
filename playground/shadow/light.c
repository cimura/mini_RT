#include "light.h"
#include "minirt.h"

void	set_light_ratio(t_light_ratio *light, t_rgb rgb, double coefficient)
{
	light->red = rgb.red / 255 * coefficient;
	light->green = rgb.green /255 * coefficient;
	light->blue = rgb.blue / 255 * coefficient;
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

int	calculate_color(t_world world, t_object *objects, t_vector dir_vec, t_vector intersection_point)
{
	double	normal_dot_incidence;
	double	inverse_dot_reflection;

	t_vector	incidence_vec;
	t_vector	reflection_vec;
	t_vector	inverse_camera_orientation_vec;

	t_light_info	light_info;

	t_light	light;
	t_ambient_lightning	ambient_lightning;

	light = world.light;
	ambient_lightning = world.ambient_lightning;
	incidence_vec = normalize_vector(subst_vector(light.coordinates_vec, intersection_point));
	normal_dot_incidence = inner_product(objects->orientation_vec, incidence_vec);
	//printf("%f\n", normal_dot_incidence);
	if (normal_dot_incidence < 0.0)
		normal_dot_incidence = 0.0;
	if (normal_dot_incidence > 1.0)
		normal_dot_incidence = 1.0;

	reflection_vec = subst_vector(multi_vector(objects->orientation_vec, 2 * normal_dot_incidence), incidence_vec);
	inverse_camera_orientation_vec = normalize_vector(multi_vector(dir_vec, -1));
	inverse_dot_reflection = inner_product(inverse_camera_orientation_vec, reflection_vec);

	if (inverse_dot_reflection < 0.0)
		inverse_dot_reflection = 0.0;
	if (inverse_dot_reflection > 1.0)
		inverse_dot_reflection = 1.0;

	set_light_ratio(&light_info.ambient_coefficient, objects->rgb, AMBIENT_COEFFICIENT);
	//printf("%f\n", objects->rgb.blue);
	set_light_ratio(&light_info.ambient_light, ambient_lightning.rgb, ambient_lightning.ratio);
	light_info.ambient_light = multi_light_ratio(light_info.ambient_light, light_info.ambient_coefficient);
	set_light_ratio(&light_info.diffuse_coefficient, objects->rgb, DIFFUSE_COEFFICIENT);
	set_light_ratio(&light_info.diffuse_light, light.rgb, light.ratio * normal_dot_incidence);
	light_info.diffuse_light = multi_light_ratio(light_info.diffuse_light, light_info.diffuse_coefficient);
	set_light_ratio(&light_info.specular_coefficient, objects->rgb, SPECULAR_COEFFICIENT);
	set_light_ratio(&light_info.specular_light, light.rgb, light.ratio * pow(inverse_dot_reflection, SHININESS));
	light_info.specular_light = multi_light_ratio(light_info.specular_light, light_info.specular_coefficient);
	light_info.result_color = add_light_ratio(light_info.ambient_light, light_info.diffuse_light);
	light_info.result_color = add_light_ratio(light_info.result_color, light_info.specular_light);

	return (rgb_to_colorcode(light_info.result_color));
}