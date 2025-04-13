/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:04:15 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/13 15:56:35 by ttakino          ###   ########.fr       */
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

t_uv	get_uv_on_cube_map(const t_cube_map *map, t_texture *tex)
{
	t_uv	top_left_pixel;

	tex->fase_side_len = tex->height / 4;
	//printf("%d", tex->fase_side_len);
	if (map->fase == PLUS_X)
	{
		top_left_pixel.u = tex->width / 2 - tex->fase_side_len / 2;
		top_left_pixel.v = tex->fase_side_len * 2;
	}
	//else if (map->fase == MINUS_X)
	//{
	//	top_left_pixel.u = tex->width / 2 - tex->fase_side_len / 2;
	//	top_left_pixel.v = 0;
	//}
	//if (map->fase == PLUS_Y)
	//{
	//	top_left_pixel.u = tex->width / 2 + tex->fase_side_len / 2;
	//	top_left_pixel.v = tex->fase_side_len;
	//}
	//else if (map->fase == MINUS_X)
	//{
	//	top_left_pixel.u = tex->width / 2 - tex->fase_side_len / 2 - tex->fase_side_len;
	//	top_left_pixel.v = tex->fase_side_len;
	//}
	//else if (map->fase == PLUS_Z)
	//{
	//	top_left_pixel.u = tex->width / 2 - tex->fase_side_len / 2;
	//	top_left_pixel.v = tex->height - tex->fase_side_len;
	//}
	//else if (map->fase == MINUS_Z)
	//{
	//	top_left_pixel.u = tex->width / 2 - tex->fase_side_len / 2;
	//	top_left_pixel.v = tex->fase_side_len;
	//}
	//if (map->uv.x < 0 || map->uv.y > 1.0)
	//printf("(%lf,%lf)", map->uv.x, map->uv.y);
	top_left_pixel.u += (int)(map->uv.x * tex->fase_side_len) % tex->fase_side_len;
	top_left_pixel.v += (int)(map->uv.y * tex->fase_side_len) % tex->fase_side_len;
	//printf("(%d,%d)", top_left_pixel.u, top_left_pixel.v);
	return (top_left_pixel);
}

void	texture_set_normal(t_intersection *i, t_texture *normal_tex)
{
	t_vector	tex_normal;
	t_cube_map	map;
	t_uv		uv;

	if (i->object->identifier == SPHERE)
		map = get_uv_on_sphere(&i->coordinates_vec, i->object, CUBE);
	//else if (object->identifier == PLANE)
	//	;
	//else if (object->identifier == CYLINDER)
	//	;
	uv = get_uv_on_cube_map(&map, normal_tex);
	// if ( != CUBE)
		//uv.u = (int)(map.uv.x * normal_tex->width) % normal_tex->width;
		//uv.v = (int)(map.uv.y * normal_tex->height) % normal_tex->height;

	//if ((uv.v * normal_tex->width + uv.u) * normal_tex->channels + 2 > normal_tex->width * normal_tex->height)
	//	printf("(%d,%d)", uv.u, uv.v);

	t_vector	tangent = calculate_tangent(&i->normal_vec);
	t_vector	bitangent = calculate_bitangent(&tangent, &i->normal_vec);
	t_vector	result;

	tex_normal = texture_get_normal(normal_tex, uv.u, uv.v);
	result
		= add_vector(multi_vector(tangent, tex_normal.x), multi_vector(bitangent, tex_normal.y));
	result
		= add_vector(result, multi_vector(i->normal_vec, tex_normal.z));
	i->normal_vec = normalize_vector(result);
}

//void	texture_set_color(t_intersection *i, t_texture *color_tex)
//{
//	t_cube_map	map;
//	t_uv		uv;

//	if (i->object->identifier == SPHERE)
//		map = get_uv_on_sphere(&i->coordinates_vec, i->object, CUBE);
//	//else if (object->identifier == PLANE)
//	//	;
//	//else if (object->identifier == CYLINDER)
//	//	;
//	uv = get_uv_on_cube_map(&map, color_tex);
//	// if ( != CUBE)
//		//uv.u = (int)(map.uv.x * color_tex->width) % color_tex->width;
//		//uv.v = (int)(map.uv.y * color_tex->height) % color_tex->height;
//	i->object->material.diffuse = texture_get_color(color_tex, uv.u, uv.v);
//}

void	texture_mapping(t_list *tex_lst, t_intersection *i)
{
	t_texture	*tex;

	while (tex_lst != NULL)
	{
		tex = (t_texture *)tex_lst->content;
		if (tex->identifier == NORMAL)
			texture_set_normal(i, tex);
		//else if (tex->identifier == COLOR)
		//	texture_set_color(i, tex);
		tex_lst = tex_lst->next;
	}
}
