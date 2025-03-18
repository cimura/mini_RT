#include "renderer.h"

static bool	is_under_shadow(t_world world, t_vector intersection_vec)
{
	t_vector	shadow_ray_vec;
	t_ray		shadow_ray;
	double		shadow_ray_len;
	double		distance;

	shadow_ray_vec = subst_vector(world.light.coordinates_vec, intersection_vec);
	shadow_ray_len = len_vector(shadow_ray_vec);
	shadow_ray.coordinates_vec = add_vector(intersection_vec, multi_vector(shadow_ray_vec, EPSILON));
	shadow_ray.orientation_vec = normalize_vector(shadow_ray_vec);
	distance = find_intersection_minimum_distance(world, shadow_ray).t;
	if (distance >= 0 && distance < shadow_ray_len)
		return (true);
	return (false);
}

// xxx_coefficient: 反射係数 物体の表面の色によって変わる
// xxx_light:		光の強度xあたる向きの内積 光源の色によって変わる

static t_light_ratio	calculate_ambient_light_ratio(t_ambient_lightning ambient_lightning, t_object object)
{
	t_light_ratio	ambient_coefficient;
	t_light_ratio	ambient_light;

	set_light_ratio(&ambient_coefficient, object.rgb, AMBIENT_COEFFICIENT);
	set_light_ratio(&ambient_light, ambient_lightning.rgb, ambient_lightning.ratio);
	return (multi_light_ratio(ambient_light, ambient_coefficient));
}

static t_light_ratio	calculate_diffuse_light_ratio(t_light light, t_object object, double normal_dot_incidence)
{
	t_light_ratio	diffuse_coefficient;
	t_light_ratio	diffuse_light;

	set_light_ratio(&diffuse_coefficient, object.rgb, DIFFUSE_COEFFICIENT);
	set_light_ratio(&diffuse_light, light.rgb, light.ratio * normal_dot_incidence);
	return (multi_light_ratio(diffuse_light, diffuse_coefficient));
}

static t_light_ratio calculate_specular_light_ratio(t_light light, t_object object, t_vector dir_vec, t_vector reflection_vec)
{
	t_light_ratio	specular_coefficient;
	t_light_ratio	specular_light;
	// 視線ベクトルの逆ベクトル
	t_vector		inverse_camera_orientation_vec;
	// 視線逆ベクトルと光源の正反射ベクトルの内積
	double			inverse_dot_reflection;

	inverse_camera_orientation_vec = normalize_vector(multi_vector(dir_vec, -1));
	inverse_dot_reflection = calculate_inner_product(inverse_camera_orientation_vec, reflection_vec);
	double_compressor(&inverse_dot_reflection, 0.0, 1.0);
	set_light_ratio(&specular_coefficient, object.rgb, SPECULAR_COEFFICIENT);
	set_light_ratio(&specular_light, light.rgb, light.ratio * pow(inverse_dot_reflection, SHININESS));
	return (multi_light_ratio(specular_light, specular_coefficient));
}

// 交点があったピクセルの色を計算する
int	calculate_pixel_color(t_world world, t_intersection i, t_ray ray)
{
	// 直接光の入射ベクトル
	t_vector			incidence_vec;
	// 法線ベクトルと入射ベクトルの内積
	double				normal_dot_incidence;
	// 光源の正反射ベクトル
	t_vector			reflection_vec;
	t_light_ratio		result_light;

	// 直接光の入射ベクトル
	incidence_vec = normalize_vector(subst_vector(world.light.coordinates_vec, i.coordinates_vec));
	result_light = calculate_ambient_light_ratio(world.ambient_lightning, i.object);
	// 影の中にいたら環境光のみ
	if (is_under_shadow(world, i.coordinates_vec) == true)
		return (rgb_to_colorcode(result_light));
	// 法線ベクトルと入射ベクトルの内積 これを0-1の範囲にする(負の値の時は光は当たらないため)
	normal_dot_incidence = calculate_inner_product(i.normal_vec, incidence_vec);
	if (normal_dot_incidence < 0)
		return (rgb_to_colorcode(result_light));
	double_compressor(&normal_dot_incidence, 0.0, 1.0);
	result_light = add_light_ratio(result_light, calculate_diffuse_light_ratio(world.light, i.object, normal_dot_incidence));
	reflection_vec = subst_vector(multi_vector(i.normal_vec, 2 * normal_dot_incidence), incidence_vec);
	result_light = add_light_ratio(result_light, calculate_specular_light_ratio(world.light, i.object, ray.orientation_vec, reflection_vec));
	return (rgb_to_colorcode(result_light));
}
