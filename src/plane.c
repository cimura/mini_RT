/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:57:50 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/17 23:13:31 by ttakino          ###   ########.fr       */
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

t_vector2	get_vec2_on_plane(const t_vector3 *intersection_vec,
	const t_object *plane)
{
	t_vector2	on_map;
	t_vector3	on_plane;
	double		u_scale;
	double		v_scale;

	on_plane = subst_vector(*intersection_vec, plane->coordinates_vec);
	u_scale = PLANE_TEX_WIDTH;
	v_scale = PLANE_TEX_HEIGHT;
	//on_map.x = on_plane.x / u_scale;
	//on_map.y = on_plane.y / v_scale;
	//on_map.x = fabs((on_plane.x - u_scale * (int)(on_plane.x / u_scale)) / u_scale);
	//on_map.y = fabs((on_plane.y - v_scale * (int)(on_plane.y / v_scale)) / v_scale);
	//on_map.x = fmod(on_plane.x / u_scale, 1.0);
	//if (on_map.x < 0)
	//	on_map.x += 1.0;
	//on_map.y = fmod(on_plane.z / v_scale, 1.0);
	//if (on_map.y < 0)
	//	on_map.y += 1.0;
	on_map.x = on_plane.x;
	on_map.y = on_plane.z;
	if (on_map.x < 0 || on_map.x > 1)
		on_map.x = 0;
	if (on_map.y < 0 || on_map.y > 1)
		on_map.y = 0;
	//on_map.x = (int)(on_plane.x / u_scale);
	//on_map.y = (int)(on_plane.y / v_scale);
	//if (on_map.x < 0 || on_map.x > 1 || on_map.y < 0 || on_map.y > 1)
	//	printf("(%lf,%lf)", on_map.x, on_map.y);
	//on_map.x = 1;
	//on_map.y = 1;
	return (on_map);
}
