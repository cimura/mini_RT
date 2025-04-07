/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catadioptric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:23:24 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/08 00:03:02 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void	catadioptric_vars_init(t_catadioptric_vars *catadioptric_vars,
	const t_intersection *intersection, const t_ray *ray)
{
	catadioptric_vars->inverse_ray_vec
		= multi_vector(ray->orientation_vec, -1);
	catadioptric_vars->inverse_ray_dot_normal
		= inner_product(catadioptric_vars->inverse_ray_vec,
			intersection->normal_vec);
}

static void	set_catadioptric_vars(t_catadioptric_vars *cv,
	const t_world *world, const t_intersection *intersection)
{
	double	rfr_2_1;

	cv->refraction_index1 = world->global_refractive_index;
	cv->refraction_index2 = intersection->object->material.refractive_index;
	if (intersection->hit_on_back == true)
	{
		cv->refraction_index1 = intersection->object->material.refractive_index;
		cv->refraction_index2 = world->global_refractive_index;
	}
	rfr_2_1 = cv->refraction_index2 / cv->refraction_index1;
	cv->cos1 = cv->inverse_ray_dot_normal;
	cv->cos2 = (cv->refraction_index1 / cv->refraction_index2)
		* sqrt(pow(rfr_2_1, 2) - (1 - pow(cv->cos1, 2)));
	cv->omega = rfr_2_1 * cv->cos2 - cv->cos1;
	cv->p_polarized_light
		= (rfr_2_1 * cv->cos1 - cv->cos2) / (rfr_2_1 * cv->cos1 + cv->cos2);
	cv->s_polarized_light = -1 * cv->omega / (rfr_2_1 * cv->cos2 + cv->cos1);
	cv->reflectance_index
		= (pow(cv->p_polarized_light, 2) + pow(cv->s_polarized_light, 2)) / 2;
}

void	case_use_thin_surfase(t_catadioptric_vars *catadioptric_vars,
	const t_world *world, t_intersection *intersection, t_ray *rfr_ray)
{
	if (intersection->object->material.use_thin_surfase == true)
	{
		intersection->hit_on_back = true;
		catadioptric_vars_init(catadioptric_vars, intersection, rfr_ray);
		set_catadioptric_vars(catadioptric_vars, world, intersection);
		*rfr_ray = get_refraction_ray(catadioptric_vars, intersection, rfr_ray);
	}
}

t_dcolor	calculate_catadioptric_radiance(const t_world *world,
	t_intersection *intersection, const t_ray *ray, int recursion_level)
{
	t_dcolor			color;
	t_catadioptric_vars	catadioptric_vars;
	t_ray				rfl_ray;
	t_ray				rfr_ray;

	color = dcolor_init(0, 0, 0);
	if (intersection->object->material.use_perfect_reflectance == false)
		return (color);
	catadioptric_vars_init(&catadioptric_vars, intersection, ray);
	rfl_ray = get_reflection_ray(&catadioptric_vars, intersection);
	color = dcolor_multi(ray_trace_recursive(world, &rfl_ray,
				recursion_level + 1),
			intersection->object->material.catadioptric_factor);
	if (intersection->object->material.use_refraction == false)
		return (color);
	set_catadioptric_vars(&catadioptric_vars, world, intersection);
	rfr_ray = get_refraction_ray(&catadioptric_vars, intersection, ray);
	case_use_thin_surfase(&catadioptric_vars, world, intersection, &rfr_ray);
	color = dcolor_coef_multi(color, catadioptric_vars.reflectance_index);
	color = dcolor_add(color, dcolor_coef_multi(dcolor_multi(
					ray_trace_recursive(world, &rfr_ray, recursion_level + 1),
					intersection->object->material.catadioptric_factor),
				1.0 - catadioptric_vars.reflectance_index));
	return (color);
}
