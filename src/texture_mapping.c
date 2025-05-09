/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:04:15 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/25 12:19:49 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	case_loop_mapping(t_vector2 *on_map)
{
	if (on_map->x < 0)
		on_map->x = 1 - fmod(fabs(on_map->x), 1.0);
	else
		on_map->x = fmod(on_map->x, 1.0);
	if (on_map->y < 0)
		on_map->y = 1 - fmod(fabs(on_map->y), 1.0);
	else
		on_map->y = fmod(on_map->y, 1.0);
}

void	texture_set_normal(t_intersection *i, t_texture *normal_tex)
{
	t_vector3		result_normal_vec;
	t_basis_vectors	basis_vec;
	t_vector3		normalvec_in_tex;
	t_vector2		on_map;
	t_uv			uv;

	if (i->object->identifier == SPHERE)
		on_map = get_vec2_on_sphere(i, i->object);
	else if (i->object->identifier == PLANE)
		on_map = get_vec2_on_plane(i, i->object, normal_tex);
	else if (i->object->identifier == CYLINDER)
		on_map = get_vec2_on_cylinder(i, i->object, normal_tex);
	if (on_map.x < 0 || on_map.y < 0 || on_map.x > 1 || on_map.y > 1)
		return ;
	uv.u = (int)(on_map.x * normal_tex->width) % normal_tex->width;
	uv.v = (int)(on_map.y * normal_tex->height) % normal_tex->height;
	normalvec_in_tex = texture_get_normal(normal_tex, uv.u, uv.v);
	basis_vec = get_basis_vectors_from_normal_vec(&i->normal_vec);
	result_normal_vec
		= add_vector(multi_vector(basis_vec.x_vector, normalvec_in_tex.x),
			multi_vector(basis_vec.y_vector, normalvec_in_tex.y));
	result_normal_vec
		= add_vector(result_normal_vec,
			multi_vector(i->normal_vec, normalvec_in_tex.z));
	i->normal_vec = normalize_vector(result_normal_vec);
}

void	texture_set_color(t_intersection *i, t_texture *color_tex)
{
	t_vector2	on_map;
	t_uv		uv;

	i->object->material.diffuse = i->object->material.original_diffuse;
	if (i->object->identifier == SPHERE)
		on_map = get_vec2_on_sphere(i, i->object);
	else if (i->object->identifier == PLANE)
		on_map = get_vec2_on_plane(i, i->object, color_tex);
	else if (i->object->identifier == CYLINDER)
		on_map = get_vec2_on_cylinder(i, i->object, color_tex);
	if (on_map.y == -1)
		return ;
	if (on_map.x < 0 || on_map.y < 0 || on_map.x > 1 || on_map.y > 1)
		return ;
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
