/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:57:50 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:54:04 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	set_plane_intersection(t_intersection *i, t_object *plane,
	const t_ray *ray)
{
	t_vector3	plane_to_start;
	double		pts_dot_po;
	double		dir_dot_po;

	plane_to_start = subst_vector(ray->coordinates_vec, plane->coordinates_vec);
	pts_dot_po
		= inner_product(plane_to_start, plane->orientation_vec);
	dir_dot_po
		= inner_product(ray->orientation_vec, plane->orientation_vec);
	i->t = -1 * (pts_dot_po / dir_dot_po);
	if (i->t < 0)
		return ;
	i->coordinates_vec
		= add_vector(ray->coordinates_vec,
			multi_vector(ray->orientation_vec, i->t));
	i->object = plane;
}

void	set_plane_normal_vector(t_intersection *intersection,
	const t_object *plane, const t_ray *ray)
{
	t_vector3	normal_vector;
	double		ray_dot_normal;

	normal_vector = plane->orientation_vec;
	intersection->hit_on_back = false;
	ray_dot_normal
		= inner_product(ray->orientation_vec, normal_vector);
	if (ray_dot_normal >= 0)
		normal_vector = multi_vector(normal_vector, -1);
	normal_vector = normalize_vector(normal_vector);
	intersection->normal_vec = normal_vector;
}

t_vector2	get_vec2_on_plane(const t_intersection *intersection,
	const t_object *plane)
{
	t_vector2		on_map;
	t_vector3		on_plane;
	t_basis_vectors	basis_vec;

	on_map.x = -1;
	on_map.y = -1;
	basis_vec = get_basis_vectors_from_normal_vec(&intersection->normal_vec);
	on_plane
		= subst_vector(intersection->coordinates_vec, plane->coordinates_vec);
	on_map.x = inner_product(on_plane, basis_vec.u);
	on_map.y = inner_product(on_plane, basis_vec.v);
	on_map.x = fmod(on_map.x, 1.0);
	on_map.y = fmod(on_map.y, 1.0);
	if (on_map.x < 0)
		on_map.x += 1.0;
	if (on_map.y < 0)
		on_map.y += 1.0;
	return (on_map);
}
