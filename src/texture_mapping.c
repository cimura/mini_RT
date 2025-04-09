/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:04:15 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/10 00:05:07 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	set_bumpmap_normal_vector(t_intersection *i, t_texture *normal_tex,
	const t_object *object)
{
	t_xy	uv;
	int		x;
	int		y;

	if (object->identifier == SPHERE)
		uv = get_uv_on_sphere(&i->coordinates_vec, object);
	//else if (object->identifier == PLANE)
	//	;
	//else if (object->identifier == CYLINDER)
	//	;
	x = (int)(uv.x * normal_tex->width) % normal_tex->width;
	y = (int)(uv.y * normal_tex->height) % normal_tex->height;
	printf("%d,%d  ", x, y);
	i->normal_vec = texture_get_normal(normal_tex, x, y);
}
