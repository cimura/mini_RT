/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:12 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/03 21:17:44 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

// This function returns pixel's color
t_dcolor	ray_trace_recursive(t_world world, t_ray ray, int recursion_level)
{
	t_dcolor		color;
	t_intersection	closest_intersection;

	color = dcolor_init(BACKGROUND_COLOR_RED,
		BACKGROUND_COLOR_GREEN, BACKGROUND_COLOR_BLUE);
	if (recursion_level > MAX_RECURSIVE_LEVEL)
		return (color);
	// 交点の数を計算
	closest_intersection = find_intersection_minimum_distance(world, ray);
	// 交点がない場合は背景色を置いてreturn 余分な計算を省くことができる
	if (closest_intersection.t < 0)
		return (color);
	// 法線ベクトルを計算
	calculate_intersections_normal_vector(&closest_intersection, ray);
	// Phong反射モデルに則ってピクセルの色を計算
	color = calculate_phong_radiance(world, closest_intersection, ray);
	// もし完全鏡面反射か屈折をするならばそれらの色を足す
	color = dcolor_add(color,
		calculate_catadioptric_radiance(world, closest_intersection, ray, recursion_level));
	return (color);
}

//void	debug_printer(t_xy in_screen, t_world world, t_intersection i, t_ray ray)

static t_dcolor ray_trace(t_world world, t_ray ray)
{
	t_dcolor	color;

	color = ray_trace_recursive(world, ray, 0);
	return (color);
}

static t_vector	get_rays_orientation_vector(t_xy in_screen, t_camera camera)
{
	t_vector	orientation_vec;
	t_vector	coordinates_in_screen;

	coordinates_in_screen = add_vector(multi_vector(camera.x_basis, 2 * in_screen.x / WIDTH - SCREEN_WIDTH / 2),
		multi_vector(camera.y_basis, SCREEN_HEIGHT / 2 - 2 * in_screen.y/ HEIGHT)); 
	orientation_vec = add_vector(camera.center_of_screen, coordinates_in_screen);
	return (normalize_vector(orientation_vec));
}

// いったんカメラの位置ベクトル、方向ベクトル、FOV（視野角）を固定する（原点上のx,yにスクリーンを張る）
int render_scene(t_world world)
{
	t_dcolor		color;
	// カメラから2次元スクリーン上の任意の点(x,y)の方向ベクトル
	t_ray			gaze_ray;
	// 2次元スクリーン上のxs,ys
	t_xy			in_screen;

	init_camera(&world.camera);
	gaze_ray.coordinates_vec = world.camera.coordinates_vec;
	in_screen.y = 0;
	while (in_screen.y < HEIGHT - 1)
	{
		in_screen.x = 0;
		while (in_screen.x < WIDTH - 1)
		{
			// スクリーン上の点の3次元空間における位置ベクトルを計算
			gaze_ray.orientation_vec = get_rays_orientation_vector(in_screen, world.camera);
			color = ray_trace(world, gaze_ray);
			my_pixel_put(in_screen.x, in_screen.y, world.mlx.img, rgb_to_colorcode(color));
			in_screen.x++;
		}
		in_screen.y++;
	}
	return (0);
}
