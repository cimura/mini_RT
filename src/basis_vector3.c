/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis_vector3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:01:47 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/19 14:11:39 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// t_vector3	calculate_tangent(const t_vector3 *normal)
// {
// 	t_vector3	arbitrary;
// 	t_vector3	tangent;

// 	arbitrary = init_vector(0, 1, 0);
// 	// arbitrary.x = 0;
// 	// arbitrary.y = 1;
// 	// arbitrary.z = 0;
// 	if (fabs(normal->x) > 0.9)
// 	{
// 		arbitrary = init_vector(1, 0, 0);
// 		// arbitrary.x = 1;
// 		// arbitrary.y = 0;
// 		// arbitrary.z = 0;
//     }
// 	tangent = cross_product(arbitrary, *normal);
// 	return (normalize_vector(tangent));
// }

// t_vector3	calculate_bitangent(const t_vector3 *tangent, const t_vector3 *normal)
// {
// 	return (normalize_vector(cross_product(*normal, *tangent)));
// }

t_basis_vector	get_basis_vector_from_normal_vec(const t_vector3 *normal_vec)
{
	t_basis_vector	basis_vec;
	t_vector3		arbitrary;

	arbitrary = init_vector(0, 1, 0);
	if (fabs(normal_vec->x) > 0.9)
		arbitrary = init_vector(1, 0, 0);
	basis_vec.u = normalize_vector(cross_product(arbitrary, *normal_vec));
	basis_vec.v = normalize_vector(cross_product(*normal_vec, basis_vec.u));
	return (basis_vec);
}
