/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:57:50 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/04 00:01:57 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	set_plane_intersection(t_intersection *i, t_object plane, t_ray ray)
{
	t_vector	plane_to_start;
	double		pts_dot_po;
	double		dir_dot_po;

	plane_to_start = subst_vector(ray.coordinates_vec, plane.coordinates_vec);
	pts_dot_po = calculate_inner_product(plane_to_start, plane.orientation_vec);
	dir_dot_po = calculate_inner_product(ray.orientation_vec, plane.orientation_vec);
	i->t = -1 * (pts_dot_po / dir_dot_po);
	if (i->t < 0)
		return ;
	i->coordinates_vec = add_vector(ray.coordinates_vec, multi_vector(ray.orientation_vec, i->t));
	i->object = plane;
}

void	set_plane_normal_vector(t_intersection *intersection,
	t_object plane, t_ray ray)
{
	t_vector	normal_vector;
	double		ray_dot_normal;

	normal_vector = plane.orientation_vec;
	intersection->hit_on_back = false;
	ray_dot_normal = calculate_inner_product(ray.orientation_vec, normal_vector);
	if (ray_dot_normal >= 0)
		normal_vector = multi_vector(normal_vector, -1);
	normal_vector = normalize_vector(normal_vector);
	intersection->normal_vec = normal_vector;
}
