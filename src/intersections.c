/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:59:04 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:46:24 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	swap_intersection(t_intersection *i1, t_intersection *i2)
{
	t_intersection	tmp;

	tmp = *i2;
	*i2 = *i1;
	*i1 = tmp;
}

t_intersection	find_intersection_minimum_distance(t_world world,
	const t_ray *ray)
{
	t_intersection	min_intersec;
	t_intersection	now_intersec;
	t_object		*object;

	min_intersec.t = -1;
	now_intersec.t = -1;
	while (world.objects != NULL)
	{
		object = (t_object *)world.objects->content;
		if (object->identifier == SPHERE)
			set_sphere_intersection(&now_intersec, object, ray);
		else if (object->identifier == PLANE)
			set_plane_intersection(&now_intersec, object, ray);
		else if (object->identifier == CYLINDER)
			set_cylinder_intersection(&now_intersec, object, ray);
		if (min_intersec.t < 0 && now_intersec.t >= 0)
			min_intersec = now_intersec;
		else if ((min_intersec.t < 0 && now_intersec.t >= 0)
			|| (min_intersec.t >= 0 && now_intersec.t >= 0
				&& min_intersec.t > now_intersec.t))
			min_intersec = now_intersec;
		world.objects = world.objects->next;
	}
	return (min_intersec);
}

void	calculate_intersections_normal_vector(t_intersection *i,
	const t_ray *ray)
{
	if (i->object->identifier == SPHERE)
		set_sphere_normal_vector(i, i->object, ray);
	else if (i->object->identifier == PLANE)
		set_plane_normal_vector(i, i->object, ray);
	else if (i->object->identifier == CYLINDER)
		set_cylinder_normal_vector(i, i->object, ray);
}
