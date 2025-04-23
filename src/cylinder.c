/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:40 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/23 17:28:34 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static bool	is_intersection_in_cylinder_height_range(const t_object *cylinder,
	const t_vector3 *intersection)
{
	double		i_dot_co;

	i_dot_co
		= inner_product(subst_vector(*intersection,
				cylinder->coordinates_vec), cylinder->orientation_vec);
	if (i_dot_co < 0)
		i_dot_co *= -1;
	if (i_dot_co <= cylinder->height / 2)
		return (true);
	else
		return (false);
}

void	set_cylinder_intersection(t_intersection *i, t_object *cylinder,
	const t_ray *ray)
{
	t_coefficient	coef;
	t_intersection	i1;
	t_intersection	i2;

	calculate_cylinder_intersections_num(&coef, cylinder, ray);
	if (coef.d < 0)
		return ;
	i1.t = ((-1 * coef.b) - sqrt(coef.d)) / (2 * coef.a);
	i2.t = ((-1 * coef.b) + sqrt(coef.d)) / (2 * coef.a);
	if (i1.t > i2.t)
		swap_intersection(&i1, &i2);
	if (i2.t < 0)
		return ;
	i1.coordinates_vec = add_vector(ray->coordinates_vec,
			multi_vector(ray->orientation_vec, i1.t));
	i2.coordinates_vec = add_vector(ray->coordinates_vec,
			multi_vector(ray->orientation_vec, i2.t));
	i1.object = cylinder;
	i2.object = cylinder;
	if (i1.t >= 0 && is_intersection_in_cylinder_height_range(
			cylinder, &i1.coordinates_vec) == true)
		*i = i1;
	else if (i2.t >= 0 && is_intersection_in_cylinder_height_range(
			cylinder, &i2.coordinates_vec) == true)
		*i = i2;
}

void	set_cylinder_normal_vector(t_intersection *intersection,
	const t_object *cylinder, const t_ray *ray)
{
	t_vector3	normal_vector;
	t_vector3	cc_to_intersection;
	t_vector3	normal_and_co_intersec;
	double		cti_dot_orientation;
	double		ray_dot_noramal;

	cc_to_intersection
		= subst_vector(intersection->coordinates_vec,
			cylinder->coordinates_vec);
	cti_dot_orientation
		= inner_product(cc_to_intersection,
			cylinder->orientation_vec);
	normal_and_co_intersec
		= multi_vector(cylinder->orientation_vec, cti_dot_orientation);
	normal_vector = subst_vector(cc_to_intersection, normal_and_co_intersec);
	intersection->hit_on_back = false;
	ray_dot_noramal
		= inner_product(ray->orientation_vec, normal_vector);
	if (ray_dot_noramal >= 0)
		normal_vector = multi_vector(normal_vector, -1);
	normal_vector = normalize_vector(normal_vector);
	intersection->normal_vec = normal_vector;
}

t_vector2	get_vec2_on_cylinder(const t_intersection *intersection,
	const t_object *cylinder, t_texture *tex)
{
	t_vector2		on_map;
	t_vector3		on_cylinder;
	t_basis_vectors	basis_vec;
	double			magnification;
	double			height;

	on_cylinder = subst_vector(intersection->coordinates_vec,
			cylinder->coordinates_vec);
	if (cylinder->diameter * M_PI / tex->width > cylinder->height / tex->height)
		magnification = cylinder->height / tex->height;
	else
		magnification = cylinder->diameter * M_PI / tex->width;
	height = tex->height * magnification;
	basis_vec = get_basis_vectors_from_normal_vec(&cylinder->orientation_vec);
	on_map.x = atan2(inner_product(on_cylinder, basis_vec.x_vector),
			inner_product(on_cylinder, basis_vec.y_vector))
		/ (2 * M_PI * ((tex->width * magnification)
				/ (cylinder->diameter * M_PI))) + 0.5;
	on_map.y = 1 - (inner_product(on_cylinder, cylinder->orientation_vec)
			+ height / 2) / height;
	return (on_map);
}
