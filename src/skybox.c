/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:22:20 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/19 18:36:13 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "texture.h"

t_dcolor	apply_skybox(const t_world *world, const t_ray *ray)
{
	t_dcolor	result_color;
	t_vector2	on_world_uv;
	t_uv		uv;
	double		theta;
	double		phi;

	result_color = dcolor_init(BACKGROUND_COLOR_RED,
		BACKGROUND_COLOR_GREEN, BACKGROUND_COLOR_BLUE);
	if (world->skybox == NULL)
		return (result_color);
	theta = atan2(ray->orientation_vec.z, ray->orientation_vec.x);
	phi = asin(ray->orientation_vec.y);
	on_world_uv.x = 0.5 + (theta / (2 * M_PI));
	on_world_uv.y = 0.5 - (phi / M_PI);
	uv.u = (int)(on_world_uv.x * world->skybox->width) % world->skybox->width;
	uv.v = (int)(on_world_uv.y * world->skybox->height) % world->skybox->height;
	result_color = texture_get_color(world->skybox, uv.u, uv.v);
	return (result_color);
}
