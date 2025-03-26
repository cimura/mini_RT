/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catadioptric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:23:24 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/26 23:20:12 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static t_ray	get_reflection_ray(t_intersection intersection,
	t_vector inverce_ray_vec, double inverce_ray_dot_normal, t_world world)
{
	t_ray	rfl_ray;

	rfl_ray.orientation_vec = normalize_vector(subst_vector(multi_vector(
		intersection.normal_vec, inverce_ray_dot_normal * 2), inverce_ray_vec));
	rfl_ray.coordinates_vec = add_vector(intersection.coordinates_vec,
		multi_vector(rfl_ray.orientation_vec, EPSILON));
	rfl_ray.prev_refractive_index = world.global_refraction_index;
	return (rfl_ray);
}

static t_ray	get_refraction_ray(double rfr_1_2, double omega,
	t_intersection intersection, t_ray ray)
{
	t_ray	rfr_ray;

	rfr_ray.orientation_vec = normalize_vector(subst_vector(multi_vector(
		ray.orientation_vec, rfr_1_2), multi_vector(
		intersection.normal_vec, rfr_1_2 * omega)));
	rfr_ray.coordinates_vec = add_vector(intersection.coordinates_vec,
		multi_vector(rfr_ray.orientation_vec, EPSILON));
	rfr_ray.prev_refractive_index = intersection.object.material.refractive_index;
	return (rfr_ray);
}

t_dcolor	calculate_catadioptric_radiance(t_world world, t_intersection intersection, t_ray ray,
	int recursion_level)
{
	t_dcolor	color;
	t_ray		rfl_ray;
	t_ray		rfr_ray;
	double		refraction_index1;
	double		refraction_index2;
	t_vector	inverce_ray_vec;
	double		inverce_ray_dot_normal;
	double		rfr_2_1;
	double		cos1;
	double		cos2;
	double		omega;
	double		p_polarized_light;
	double		s_polarized_light;
	double		reflectance_index;
	bool		ray_from_back;

	ray_from_back = false;
	color = dcolor_init(0, 0, 0);
	if (intersection.object.material.use_perfect_reflectance == false)
		return (color);
	inverce_ray_vec = multi_vector(ray.orientation_vec, -1);
	inverce_ray_dot_normal = calculate_inner_product(inverce_ray_vec,
		intersection.normal_vec);

	//refraction_index1 = world.global_refraction_index;
	//refraction_index2 = intersection.object.material.refractive_index;
	if (inverce_ray_dot_normal < 0)
	{
		//swap_double(&refraction_index1, &refraction_index2);
		intersection.normal_vec = multi_vector(intersection.normal_vec, -1);
		inverce_ray_dot_normal = calculate_inner_product(inverce_ray_vec,
			intersection.normal_vec);
		ray_from_back = true;
	}
	rfl_ray =
		get_reflection_ray(intersection, inverce_ray_vec, inverce_ray_dot_normal, world);
	color =
		dcolor_multi(ray_trace_recursive(world, rfl_ray,
		recursion_level + 1), intersection.object.material.catadioptric_factor);
	if (intersection.object.material.use_refraction == false)
		return (color);
	refraction_index1 = ray.prev_refractive_index;
	refraction_index2 = intersection.object.material.refractive_index;
	if (ray_from_back == true)
		refraction_index2 = world.global_refraction_index;
	rfr_2_1 = refraction_index2 / refraction_index1;
	cos1 = inverce_ray_dot_normal;
	cos2 = (refraction_index1 / refraction_index2)
		* sqrt(pow(rfr_2_1, 2) - (1 - pow(cos1, 2)));
	omega = rfr_2_1 * cos2 - cos1;
	rfr_ray = get_refraction_ray(refraction_index1 / refraction_index2, omega,
		intersection, ray);
	p_polarized_light = (rfr_2_1 * cos1 - cos2) / (rfr_2_1 * cos1 + cos2);
	s_polarized_light = -1 * omega / (rfr_2_1 * cos2 + cos1);
	reflectance_index = (pow(p_polarized_light, 2) + pow(s_polarized_light, 2)) / 2;
	color = dcolor_coef_multi(color, reflectance_index);
	color = dcolor_add(color, dcolor_coef_multi(dcolor_multi(ray_trace_recursive(world, rfr_ray,
		recursion_level + 1),
		intersection.object.material.catadioptric_factor), 1.0 - reflectance_index));
	return (color);
}
