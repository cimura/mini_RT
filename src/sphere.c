/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:18 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/13 14:27:34 by ttakino          ###   ########.fr       */
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

void	set_uv_on_cube_map(t_cube_map *on_map, const t_vector *on_sphere)
{
	double	abs_x;
	double	abs_y;
	double	abs_z;

	abs_x = fabs(on_sphere->x);
	abs_y = fabs(on_sphere->y);
	abs_z = fabs(on_sphere->z);
	if (abs_x >= abs_y && abs_x >= abs_z)
	{
		on_map->fase = PLUS_X;
		if (on_sphere->x < 0)
			on_map->fase = MINUS_X;
		on_map->uv.x = (on_sphere->y / abs_x + 1.0) * 0.5;
		on_map->uv.y = (on_sphere->z / abs_x + 1.0) * 0.5;
	}
	else if (abs_y >= abs_x && abs_y >= abs_z)
	{
		on_map->fase = PLUS_Y;
		if (on_sphere->y < 0)
			on_map->fase = MINUS_Y;
		on_map->uv.x = (on_sphere->x / abs_y + 1.0) * 0.5;
		on_map->uv.y = (on_sphere->z / abs_y + 1.0) * 0.5;
	}
	else
	{
		on_map->fase = PLUS_Z;
		if (on_sphere->z < 0)
			on_map->fase = MINUS_Z;
		on_map->uv.x = (on_sphere->y / abs_z + 1.0) * 0.5;
		on_map->uv.y = (on_sphere->x / abs_z + 1.0) * 0.5;
	}
}

t_cube_map	get_uv_on_sphere(const t_vector *intersection_vec,
	const t_object *sphere, int map_type)
{
	t_cube_map		on_map;
	t_vector		on_sphere;
	double			theta;
	double			phi;

	on_sphere = subst_vector(*intersection_vec, sphere->coordinates_vec);
	if (map_type == RECTANGLE)
	{
		//on_sphere = *intersection_vec;
		theta = atan2(on_sphere.z, on_sphere.x);
		phi = asin(on_sphere.y / (sphere->diameter / 2));
		on_map.fase = ONE_SIDE;
		on_map.uv.x = 0.5 + (theta / (2 * M_PI));
		on_map.uv.y = 0.5 - (phi / M_PI);
	}
	else if (map_type == CUBE)
	{
		on_sphere = normalize_vector(on_sphere);
		set_uv_on_cube_map(&on_map, &on_sphere);
	}
	return (on_map);
}
