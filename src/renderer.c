/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:12 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/10 00:10:35 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "shader.h"

// This function returns pixel's color
t_dcolor	ray_trace_recursive(const t_world *world, const t_ray *ray,
	int recursion_level)
{
	t_dcolor		color;
	t_intersection	closest_intersection;

	color = dcolor_init(BACKGROUND_COLOR_RED,
			BACKGROUND_COLOR_GREEN, BACKGROUND_COLOR_BLUE);
	if (recursion_level > MAX_RECURSIVE_LEVEL)
		return (color);
	closest_intersection = find_intersection_minimum_distance(*world, ray);
	if (closest_intersection.t < 0)
		return (color);
	calculate_intersections_normal_vector(&closest_intersection, ray);
	//set_bumpmap_normal_vector(&closest_intersection,
	//	&closest_intersection.object->normal_tex, closest_intersection.object);
	color = shader(world, &closest_intersection, ray);
	color = dcolor_add(color, calculate_catadioptric_radiance(
				world, &closest_intersection, ray, recursion_level));
	return (color);
}

static t_vector	get_rays_orientation_vector(t_xy in_screen, t_camera camera)
{
	t_vector	orientation_vec;
	t_vector	coordinates_in_screen;

	coordinates_in_screen
		= add_vector(multi_vector(camera.x_basis,
				2 * in_screen.x / WIDTH - SCREEN_WIDTH / 2), multi_vector(
				camera.y_basis, SCREEN_HEIGHT / 2 - 2 * in_screen.y / HEIGHT));
	orientation_vec
		= add_vector(camera.center_of_screen, coordinates_in_screen);
	return (normalize_vector(orientation_vec));
}

void	print_on_window(t_world *world, int width, int height)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_pixel_put(x, y, world->mlx.img,
				rgb_to_colorcode(world->frame_buffer[y][x]));
			x++;
		}
		y++;
	}
}

int	renderer(t_world *world)
{
	t_dcolor		color;
	t_ray			gaze_ray;
	t_xy			in_screen;

	init_camera(&world->camera);
	gaze_ray.coordinates_vec = world->camera.coordinates_vec;
	in_screen.y = 0;
	while (in_screen.y < HEIGHT - 1)
	{
		in_screen.x = 0;
		while (in_screen.x < WIDTH - 1)
		{
			gaze_ray.orientation_vec
				= get_rays_orientation_vector(in_screen, world->camera);
			color = ray_trace_recursive(world, &gaze_ray, 0);
			world->frame_buffer[(int)in_screen.y][(int)in_screen.x] = color;
			in_screen.x++;
		}
		in_screen.y++;
	}
	if (anti_aliasing(world) != 0)
		return (1);
	print_on_window(world, WIDTH, HEIGHT);
	return (0);
}
