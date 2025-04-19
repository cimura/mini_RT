/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:12 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/17 22:34:16 by ttakino          ###   ########.fr       */
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
	texture_mapping(closest_intersection.object->textures, &closest_intersection);
	color = shader(world, &closest_intersection, ray);
	color = dcolor_add(color, calculate_catadioptric_radiance(
				world, &closest_intersection, ray, recursion_level));
	return (color);
}

static t_vector3	get_rays_orientation_vector(t_vector2 in_screen, t_camera camera)
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

void *render_thread(void *arg)
{
	t_thread_data *data = (t_thread_data *)arg;
	t_dcolor color;
	t_ray gaze_ray;
	t_vector2 in_screen;

	gaze_ray.coordinates_vec = data->world->camera.coordinates_vec;
	in_screen.y = data->start_y;
	while (in_screen.y < data->end_y)
	{
		in_screen.x = 0;
		while (in_screen.x < WIDTH)
		{
			gaze_ray.orientation_vec = get_rays_orientation_vector(in_screen, data->world->camera);
			color = ray_trace_recursive(data->world, &gaze_ray, 0);
			my_pixel_put(in_screen.x, in_screen.y, data->world->mlx.img, rgb_to_colorcode(color));
			in_screen.x++;
		}
		in_screen.y++;
	}
	return (NULL);
}

int	renderer(t_world *world)
{
	pthread_t threads[NUM_THREADS];
	t_thread_data thread_data[NUM_THREADS];
	int i;
	int rows_per_thread;

	init_camera(&world->camera);
	rows_per_thread = HEIGHT / NUM_THREADS;
	i = 0;

	// Create threads
	while (i < NUM_THREADS)
	{
		thread_data[i].world = world;
		thread_data[i].start_y = i * rows_per_thread;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_y = HEIGHT;
		else
			thread_data[i].end_y = (i + 1) * rows_per_thread;
		if (pthread_create(&threads[i], NULL, render_thread, &thread_data[i]) != 0)		
			return (1);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
