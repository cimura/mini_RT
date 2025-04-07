/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:26 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/08 00:07:56 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	subst_vector(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector	add_vector(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	multi_vector(t_vector v, double c)
{
	t_vector	result;

	result.x = v.x * c;
	result.y = v.y * c;
	result.z = v.z * c;
	return (result);
}

double	len_vector(t_vector v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

// ベクトルを正規化する関数
t_vector	normalize_vector(t_vector v)
{
	double		magnitude;
	t_vector	nv;

	magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	nv.x = v.x / magnitude;
	nv.y = v.y / magnitude;
	nv.z = v.z / magnitude;
	return (nv);
}
