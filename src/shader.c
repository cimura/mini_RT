/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:07 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:51:27 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

static bool	is_under_shadow(const t_world *world, const t_light *light,
	t_vector3 intersection_vec)
{
	t_vector3	shadow_ray_vec;
	t_ray		shadow_ray;
	double		shadow_ray_len;
	double		distance;

	shadow_ray_vec = subst_vector(light->coordinates_vec, intersection_vec);
	shadow_ray.orientation_vec = normalize_vector(shadow_ray_vec);
	shadow_ray.coordinates_vec
		= add_vector(intersection_vec,
			multi_vector(shadow_ray.orientation_vec, EPSILON));
	shadow_ray_len = len_vector(shadow_ray_vec);
	distance = find_intersection_minimum_distance(*world, &shadow_ray).t;
	if (distance >= 0 && distance < shadow_ray_len)
		return (true);
	return (false);
}

static t_dcolor	calculate_diffuse_color(const t_light *light,
	const t_object *object, double normal_dot_incidence)
{
	t_dcolor	diffuse_light;

	diffuse_light = dcolor_coef_multi(light->intensity, normal_dot_incidence);
	return (dcolor_multi(diffuse_light, object->material.diffuse));
}

static t_dcolor	calculate_specular_color(const t_light *light,
	const t_object *object, t_vector3 dir_vec, t_vector3 reflection_vec)
{
	t_dcolor		specular_light;
	t_vector3		inverse_dir_vec;
	double			inverse_dot_reflection;

	inverse_dir_vec = normalize_vector(multi_vector(dir_vec, -1));
	inverse_dot_reflection
		= inner_product(inverse_dir_vec, reflection_vec);
	double_compressor(&inverse_dot_reflection, 0.0, 1.0);
	specular_light
		= dcolor_coef_multi(light->intensity,
			pow(inverse_dot_reflection, object->material.shinness));
	return (dcolor_multi(specular_light, object->material.specular));
}

static t_dcolor	calculate_onelight_radiance(const t_world *world,
	const t_light *light, const t_intersection *i, const t_ray *ray)
{
	t_vector3	incidence_vec;
	double		normal_dot_incidence;
	t_vector3	reflection_vec;
	t_dcolor	result_color;

	incidence_vec = normalize_vector(subst_vector(
				light->coordinates_vec, i->coordinates_vec));
	result_color = world->ambient_lightning.intensity;
	if (is_under_shadow(world, light, i->coordinates_vec) == true)
		return (result_color);
	normal_dot_incidence
		= inner_product(i->normal_vec, incidence_vec);
	if (normal_dot_incidence < 0)
		return (result_color);
	double_compressor(&normal_dot_incidence, 0.0, 1.0);
	result_color
		= dcolor_add(result_color,
			calculate_diffuse_color(light, i->object, normal_dot_incidence));
	reflection_vec
		= subst_vector(multi_vector(
				i->normal_vec, 2 * normal_dot_incidence), incidence_vec);
	result_color
		= dcolor_add(result_color, calculate_specular_color(light, i->object,
				ray->orientation_vec, reflection_vec));
	return (result_color);
}

t_dcolor	shader(const t_world *world, const t_intersection *i,
	const t_ray *ray)
{
	t_dcolor	color;
	t_light		*light;
	t_list		*lst;

	color = dcolor_init(0, 0, 0);
	lst = world->lights;
	while (lst != NULL)
	{
		light = (t_light *)lst->content;
		color = dcolor_add(color,
				calculate_onelight_radiance(world, light, i, ray));
		lst = lst->next;
	}
	return (color);
}
