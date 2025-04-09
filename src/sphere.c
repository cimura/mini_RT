/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:18 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/10 00:07:54 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void	calculate_sphere_intersections_num(t_coef *coef,
	const t_object *sphere, const t_ray *ray)
{
	t_vector	start_to_sphere;

	start_to_sphere
		= subst_vector(ray->coordinates_vec, sphere->coordinates_vec);
	coef->a
		= inner_product(ray->orientation_vec, ray->orientation_vec);
	coef->b
		= 2.0 * inner_product(start_to_sphere, ray->orientation_vec);
	coef->c
		= inner_product(start_to_sphere, start_to_sphere)
		- (sphere->diameter / 2.0) * (sphere->diameter / 2.0);
	coef->d = coef->b * coef->b - 4 * coef->a * coef->c;
}

void	set_sphere_intersection(t_intersection *i, t_object *sphere,
	const t_ray *ray)
{
	t_coef			coef;
	t_intersection	i1;
	t_intersection	i2;

	calculate_sphere_intersections_num(&coef, sphere, ray);
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
	i1.object = sphere;
	i2.object = sphere;
	if (i1.t >= 0)
		*i = i1;
	else if (i2.t >= 0)
		*i = i2;
}

void	set_sphere_normal_vector(t_intersection *intersection,
	const t_object *sphere, const t_ray *ray)
{
	t_vector	normal_vector;
	double		ray_dot_noraml;

	normal_vector
		= subst_vector(intersection->coordinates_vec, sphere->coordinates_vec);
	intersection->hit_on_back = false;
	ray_dot_noraml
		= inner_product(ray->orientation_vec, normal_vector);
	if (ray_dot_noraml >= 0)
	{
		normal_vector = multi_vector(normal_vector, -1);
		intersection->hit_on_back = true;
	}
	normal_vector = normalize_vector(normal_vector);
	intersection->normal_vec = normal_vector;
}

t_xy	get_uv_on_sphere(const t_vector *intersection_vec,
	const t_object *sphere)
{
	t_xy		tex;
	t_vector	on_sphere;

	on_sphere = subst_vector(*intersection_vec, sphere->coordinates_vec);
	tex.x = 0.5 + atan2(on_sphere.z, on_sphere.x) / (2 * M_PI);
	tex.y = 0.5 - asin(on_sphere.y) / M_PI;
	return (tex);
}
