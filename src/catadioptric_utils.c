/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catadioptric_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:06:37 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:40:08 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

t_ray	get_reflection_ray(const t_catadioptric_vars *catadioptric_vars,
	const t_intersection *intersection)
{
	t_ray	reflective_ray;

	reflective_ray.orientation_vec
		= normalize_vector(subst_vector(multi_vector(intersection->normal_vec,
					catadioptric_vars->inverse_ray_dot_normal * 2),
				catadioptric_vars->inverse_ray_vec));
	reflective_ray.coordinates_vec = add_vector(intersection->coordinates_vec,
			multi_vector(reflective_ray.orientation_vec, EPSILON));
	return (reflective_ray);
}

t_ray	get_refraction_ray(const t_catadioptric_vars *catadioptric_vars,
	const t_intersection *intersection, const t_ray *ray)
{
	t_ray	rfr_ray;
	double	rfr_1_2;

	rfr_1_2 = catadioptric_vars->refraction_index1
		/ catadioptric_vars->refraction_index2;
	rfr_ray.orientation_vec = normalize_vector(subst_vector(multi_vector(
					ray->orientation_vec, rfr_1_2), multi_vector(
					intersection->normal_vec, rfr_1_2
					* catadioptric_vars->omega)));
	rfr_ray.coordinates_vec = add_vector(intersection->coordinates_vec,
			multi_vector(rfr_ray.orientation_vec, EPSILON));
	return (rfr_ray);
}
