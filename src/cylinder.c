/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:40 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/22 22:13:29 by ttakino          ###   ########.fr       */
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
	t_vector2	on_map;
	t_vector3	on_cylinder;
	double		width;
	double		height;

	on_map.x = -1;
	on_map.y = -1;
	on_cylinder = subst_vector(intersection->coordinates_vec,
			cylinder->coordinates_vec);
	if (cylinder->diameter * M_PI > cylinder->height)
	{
		width = cylinder->height * tex->width / tex->height;
		height = cylinder->height;
	}
	else
	{
		width = cylinder->diameter * M_PI;
		height = cylinder->diameter * M_PI * tex->height / tex->width;
	}
	on_map.x = 0.5 + (atan2(on_cylinder.z, on_cylinder.x) / (2 * M_PI));
	on_map.y = fabs(inner_product(on_cylinder, cylinder->orientation_vec));
	return (on_map);
}
