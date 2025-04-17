/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:00:45 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/17 19:08:50 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

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
