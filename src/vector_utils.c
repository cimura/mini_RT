/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:00:45 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/22 21:45:38 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector3	init_vector(double x, double y, double z)
{
	t_vector3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double	inner_product(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3	cross_product(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_basis_vectors	get_basis_vectors_from_normal_vec(const t_vector3 *normal_vec)
{
	t_basis_vectors	basis_vec;
	t_vector3		arbitrary;

	if (fabs(normal_vec->x) > fabs(normal_vec->y))
		arbitrary = init_vector(0, 1, 0);
	else
		arbitrary = init_vector(1, 0, 0);
	basis_vec.x_vector
		= normalize_vector(cross_product(arbitrary, *normal_vec));
	basis_vec.y_vector
		= normalize_vector(cross_product(*normal_vec, basis_vec.x_vector));
	return (basis_vec);
}
