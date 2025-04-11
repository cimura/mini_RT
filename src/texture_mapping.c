/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:04:15 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/12 00:01:18 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_vector	calculate_tangent(const t_vector *normal)
{
	t_vector	arbitrary;
	t_vector	tangent;

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

t_vector	calculate_bitangent(const t_vector *tangent, const t_vector *normal)
{
	return (normalize_vector(cross_product(*normal, *tangent)));
}

void	texture_set_normal(t_intersection *i, t_texture *normal_tex)
{
	t_vector	tex_normal;
	t_xy		uv;
	int			x;
	int			y;

	if (i->object->identifier == SPHERE)
		uv = get_uv_on_sphere(&i->coordinates_vec, i->object);
	//else if (object->identifier == PLANE)
	//	;
	//else if (object->identifier == CYLINDER)
	//	;
	x = (int)(uv.x * normal_tex->width) % normal_tex->width;
	y = (int)(uv.y * normal_tex->height) % normal_tex->height;

	t_vector	tangent = calculate_tangent(&i->normal_vec);
	t_vector	bitangent = calculate_bitangent(&tangent, &i->normal_vec);
	t_vector	result;

	tex_normal = texture_get_normal(normal_tex, x, y);
	result
		= add_vector(multi_vector(tangent, tex_normal.x), multi_vector(bitangent, tex_normal.y));
	result
		= add_vector(result, multi_vector(i->normal_vec, tex_normal.z));
	i->normal_vec = normalize_vector(result);
}

void	texture_set_color(t_intersection *i, t_texture *color_tex)
{
	t_xy	uv;
	int		x;
	int		y;

	if (i->object->identifier == SPHERE)
		uv = get_uv_on_sphere(&i->coordinates_vec, i->object);
	//else if (object->identifier == PLANE)
	//	;
	//else if (object->identifier == CYLINDER)
	//	;
	x = (int)(uv.x * color_tex->width) % color_tex->width;
	y = (int)(uv.y * color_tex->height) % color_tex->height;
	i->object->material.diffuse = texture_get_color(color_tex, x, y);
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
