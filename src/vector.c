/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:26 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:52:57 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector3	subst_vector(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3	add_vector(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector3	multi_vector(t_vector3 v, double c)
{
	t_vector3	result;

	result.x = v.x * c;
	result.y = v.y * c;
	result.z = v.z * c;
	return (result);
}

double	len_vector(t_vector3 v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vector3	normalize_vector(t_vector3 v)
{
	double		magnitude;
	t_vector3	nv;

	magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	nv.x = v.x / magnitude;
	nv.y = v.y / magnitude;
	nv.z = v.z / magnitude;
	return (nv);
}
