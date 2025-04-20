/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:12 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 16:33:55 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "shader.h"

t_dcolor	ray_trace_recursive(const t_world *world, const t_ray *ray,
	int recursion_level)
{
	t_dcolor		color;
	t_intersection	closest_intersection;

	color = apply_skybox(world, ray);
	if (recursion_level > MAX_RECURSIVE_LEVEL)
		return (color);
	closest_intersection = find_intersection_minimum_distance(*world, ray);
	if (closest_intersection.t < 0)
		return (color);
	calculate_intersections_normal_vector(&closest_intersection, ray);
	texture_mapping(closest_intersection.object->textures,
		&closest_intersection);
	color = shader(world, &closest_intersection, ray);
	color = dcolor_add(color, calculate_catadioptric_radiance(
				world, &closest_intersection, ray, recursion_level));
	return (color);
}

static t_vector3	get_rays_orientation_vector(t_vector2 in_screen,
		t_camera camera)
{
	t_vector3	orientation_vec;
	t_vector3	coordinates_in_screen;

	coordinates_in_screen
		= add_vector(multi_vector(camera.x_basis,
				2 * in_screen.x / WIDTH - SCREEN_WIDTH / 2), multi_vector(
				camera.y_basis, SCREEN_HEIGHT / 2 - 2 * in_screen.y / HEIGHT));
	orientation_vec
		= add_vector(camera.center_of_screen, coordinates_in_screen);
	return (normalize_vector(orientation_vec));
}

int	renderer(t_world *world)
{
	t_dcolor		color;
	t_ray			gaze_ray;
	t_vector2		in_screen;

	init_camera(&world->camera);
	gaze_ray.coordinates_vec = world->camera.coordinates_vec;
	in_screen.y = 0;
	while (in_screen.y < HEIGHT)
	{
		in_screen.x = 0;
		while (in_screen.x < WIDTH)
		{
			gaze_ray.orientation_vec
				= get_rays_orientation_vector(in_screen, world->camera);
			color = ray_trace_recursive(world, &gaze_ray, 0);
			my_pixel_put(in_screen.x, in_screen.y,
				world->mlx.img, rgb_to_colorcode(color));
			in_screen.x++;
		}
		in_screen.y++;
	}
	return (0);
}
