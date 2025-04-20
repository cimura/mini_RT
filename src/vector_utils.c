/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:00:45 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/19 14:11:58 by ttakino          ###   ########.fr       */
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

double	abst_squared(t_vector3 v)
{
	double	result;

	result = 0;
	result += v.x * v.x;
	result += v.y * v.y;
	result += v.z * v.z;
	return (result);
}

// ベクトルの内積
double	inner_product(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// ベクトルの外積
t_vector3	cross_product(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

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
