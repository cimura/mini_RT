/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:04:15 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 13:53:14 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	texture_set_normal(t_intersection *i, t_texture *normal_tex)
{
	t_vector3		result_normal_vec;
	t_basis_vector	basis_vec;
	t_vector3		normalvec_in_tex;
	t_vector2		on_map;
	t_uv			uv;

	if (i->object->identifier == SPHERE)
		on_map = get_vec2_on_sphere(&i->coordinates_vec, i->object);
	else if (i->object->identifier == PLANE)
		on_map = get_vec2_on_plane(i, i->object, normal_tex);
	//else if (i->object->identifier == CYLINDER)
	//	;
	if (on_map.x < 0 || on_map.y < 0 || on_map.x > 1 || on_map.y > 1)
		return ;
	uv.u = (int)(on_map.x * normal_tex->width) % normal_tex->width;
	uv.v = (int)(on_map.y * normal_tex->height) % normal_tex->height;
	normalvec_in_tex = texture_get_normal(normal_tex, uv.u, uv.v);
	basis_vec = get_basis_vector_from_normal_vec(&i->normal_vec);
	result_normal_vec
		= add_vector(multi_vector(basis_vec.u, normalvec_in_tex.x),
			multi_vector(basis_vec.v, normalvec_in_tex.y));
	result_normal_vec
		= add_vector(result_normal_vec, multi_vector(i->normal_vec, normalvec_in_tex.z));
	i->normal_vec = normalize_vector(result_normal_vec);
}

void	texture_set_color(t_intersection *i, t_texture *color_tex)
{
	t_vector2	on_map;
	t_uv		uv;

	if (i->object->identifier == SPHERE)
		on_map = get_vec2_on_sphere(&i->coordinates_vec, i->object);
	else if (i->object->identifier == PLANE)
		on_map = get_vec2_on_plane(i, i->object, color_tex);
	//else if (object->identifier == CYLINDER)
	//	;
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
