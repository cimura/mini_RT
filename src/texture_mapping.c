/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:04:15 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/17 22:24:32 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_vector3	calculate_tangent(const t_vector3 *normal)
{
	t_vector3	arbitrary;
	t_vector3	tangent;

	arbitrary.x = 0;
	arbitrary.y = 1;
	arbitrary.z = 0;
	if (fabs(normal->x) > 0.9)
	{
		arbitrary.x = 1;
		arbitrary.y = 0;
		arbitrary.z = 0;
    }
	tangent = cross_product(arbitrary, *normal);
	return (normalize_vector(tangent));
}

t_vector3	calculate_bitangent(const t_vector3 *tangent, const t_vector3 *normal)
{
	return (normalize_vector(cross_product(*normal, *tangent)));
}

void	texture_set_normal(t_intersection *i, t_texture *normal_tex)
{
	t_vector3	normalvec_in_tex;
	t_vector2	on_map;
	t_uv		uv;

	if (i->object->identifier == SPHERE)
		on_map = get_vec2_on_sphere(&i->coordinates_vec, i->object);
	else if (i->object->identifier == PLANE)
		on_map = get_vec2_on_plane(&i->coordinates_vec, i->object);
	//else if (i->object->identifier == CYLINDER)
	//	;
	uv.u = (int)(on_map.x * normal_tex->width) % normal_tex->width;
	uv.v = (int)(on_map.y * normal_tex->height) % normal_tex->height;

	t_vector3	tangent = calculate_tangent(&i->normal_vec);
	t_vector3	bitangent = calculate_bitangent(&tangent, &i->normal_vec);
	t_vector3	result;

	normalvec_in_tex = texture_get_normal(normal_tex, uv.u, uv.v);
	result
		= add_vector(multi_vector(tangent, normalvec_in_tex.x), multi_vector(bitangent, normalvec_in_tex.y));
	result
		= add_vector(result, multi_vector(i->normal_vec, normalvec_in_tex.z));
	i->normal_vec = normalize_vector(result);
}

void	texture_set_color(t_intersection *i, t_texture *color_tex)
{
	t_vector2	on_map;
	t_uv		uv;

	if (i->object->identifier == SPHERE)
		on_map = get_vec2_on_sphere(&i->coordinates_vec, i->object);
	else if (i->object->identifier == PLANE)
		on_map = get_vec2_on_plane(&i->coordinates_vec, i->object);
	//else if (object->identifier == CYLINDER)
	//	;
	uv.u = (int)(on_map.x * color_tex->width) % color_tex->width;
	uv.v = (int)(on_map.y * color_tex->height) % color_tex->height;
	i->object->material.diffuse = texture_get_color(color_tex, uv.u, uv.v);
}

void	texture_mapping(t_list *tex_lst, t_intersection *i)
{
	t_texture	*tex;

	while (tex_lst != NULL)
	{
		tex = (t_texture *)tex_lst->content;
		if (tex->identifier == NORMAL)
			texture_set_normal(i, tex);
		else if (tex->identifier == COLOR)
			texture_set_color(i, tex);
		tex_lst = tex_lst->next;
	}
}
