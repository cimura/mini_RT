/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_phong_radiance.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:07 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/06 23:57:40 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static bool	is_under_shadow(t_dcolor *color, const t_world *world, t_light *light,
	const t_vector *intersection_vec, int recursion_level)
{
	t_vector	shadow_ray_vec;
	t_ray		shadow_ray;
	double		shadow_ray_len;
	t_intersection	closest_intersection;

	shadow_ray_vec = subst_vector(light->coordinates_vec, *intersection_vec);
	shadow_ray.orientation_vec = normalize_vector(shadow_ray_vec);
	shadow_ray.coordinates_vec = add_vector(*intersection_vec, multi_vector(shadow_ray.orientation_vec, EPSILON));
	shadow_ray_len = len_vector(shadow_ray_vec);
	closest_intersection = find_intersection_minimum_distance(*world, &shadow_ray);
	if (closest_intersection.t >= 0 && closest_intersection.t < shadow_ray_len)
	{
		if (closest_intersection.object->material.use_refraction == true)
		{
			(void)color;
			(void)recursion_level;
			//if (recursion_level <= 0)
			//	light->intensity = ray_trace_recursive(world, &shadow_ray, recursion_level + 1);
			//else
			//	light->intensity = dcolor_coef_multi(light->intensity, 0.0);
			return (false);
		}
		else
			return (true);
	}
	return (false);
}

// xxx_coefficient: 反射係数 物体の表面の色によって変わる
// xxx_light:		光の強度xあたる向きの内積 光源の色によって変わる

static t_dcolor	calculate_diffuse_color(const t_light *light, const t_object *object,
	double normal_dot_incidence)
{
	t_dcolor	diffuse_light;

	diffuse_light = dcolor_coef_multi(light->intensity, normal_dot_incidence);
	return (dcolor_multi(diffuse_light, object->material.diffuse));
}

static t_dcolor calculate_specular_color(const t_light *light, const t_object *object,
	t_vector dir_vec, t_vector reflection_vec)
{
	t_dcolor		specular_light;
	// 視線ベクトルの逆ベクトル
	t_vector		inverse_dir_vec;
	// 視線逆ベクトルと光源の正反射ベクトルの内積
	double			inverse_dot_reflection;

	inverse_dir_vec = normalize_vector(multi_vector(dir_vec, -1));
	inverse_dot_reflection = calculate_inner_product(inverse_dir_vec, reflection_vec);
	double_compressor(&inverse_dot_reflection, 0.0, 1.0);
	specular_light = dcolor_coef_multi(light->intensity, pow(inverse_dot_reflection, object->material.shinness));
	return (dcolor_multi(specular_light, object->material.specular));
}

// 交点があったピクセルの色を計算する
static t_dcolor	calculate_onelight_radiance(const t_world *world, const t_light *light,
	const t_intersection *i, const t_ray *ray, int recursion_level)
{
	// 直接光の入射ベクトル
	t_vector	incidence_vec;
	// 法線ベクトルと入射ベクトルの内積
	double		normal_dot_incidence;
	// 光源の正反射ベクトル
	t_vector	reflection_vec;
	t_dcolor	result_color;
	t_light		tmp;

	// 直接光の入射ベクトル
	incidence_vec = normalize_vector(subst_vector(light->coordinates_vec, i->coordinates_vec));
	result_color = world->ambient_lightning.intensity;
	// 影の中にいたら環境光のみ
	tmp = *light;
	if (is_under_shadow(&result_color, world, &tmp, &i->coordinates_vec, recursion_level) == true)
		return (result_color);
	// 法線ベクトルと入射ベクトルの内積 これを0-1の範囲にする(負の値の時は光は当たらないため)
	normal_dot_incidence = calculate_inner_product(i->normal_vec, incidence_vec);
	if (normal_dot_incidence < 0)
		return (result_color);
	double_compressor(&normal_dot_incidence, 0.0, 1.0);
	result_color = dcolor_add(result_color, calculate_diffuse_color(&tmp, i->object, normal_dot_incidence));
	reflection_vec = subst_vector(multi_vector(i->normal_vec, 2 * normal_dot_incidence), incidence_vec);
	result_color = dcolor_add(result_color, calculate_specular_color(&tmp, i->object, ray->orientation_vec, reflection_vec));
	return (result_color);
}

t_dcolor	calculate_phong_radiance(const t_world *world, const t_intersection *i,
	const t_ray *ray, int recursion_level)
{
	t_dcolor	color;
	t_light		*light;
	t_list		*lst;

	color = dcolor_init(0, 0, 0);
	lst = world->lights;
	while (lst != NULL)
	{
		light = (t_light *)lst->content;
		color = dcolor_add(color, calculate_onelight_radiance(world, light, i, ray, recursion_level));
		lst = lst->next;
	}
	return (color);
}
