/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:12 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/31 23:18:00 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

#define PERFECT_REFLECTANCE 2

// This function returns pixel's color
t_dcolor	ray_trace_recursive(t_world world, t_trajectory *trajectory,
	t_ray ray, int recursion_level)
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
		calculate_catadioptric_radiance(world, closest_intersection, trajectory, ray, recursion_level));
	return (color);
}

//void	debug_printer(t_xy in_screen, t_world world, t_intersection i, t_ray ray)

static t_dcolor ray_trace(t_world world, t_trajectory *trajectory, t_ray ray)
{
	t_dcolor	color;

	color = ray_trace_recursive(world, trajectory, ray, 0);
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

static int	trajectory_init(t_trajectory *trajectory, t_world world)
{
	int	size;

	size = ft_lstsize(world.objects) + 2;
	if (!(trajectory->objects_trajectory = malloc(size * sizeof(double))))
		return (1);
	trajectory->objects_trajectory[0] = world.scene_wide_object.material.refractive_index;
	trajectory->head_i = 0;
	trajectory->objects_trajectory[1] = -1;
	return (0);
}

// いったんカメラの位置ベクトル、方向ベクトル、FOV（視野角）を固定する（原点上のx,yにスクリーンを張る）
int render_scene(t_world world)
{
	t_dcolor		color;
	// カメラから2次元スクリーン上の任意の点(x,y)の方向ベクトル
	t_ray			gaze_ray;
	// 2次元スクリーン上のxs,ys
	t_xy			in_screen;
	// カメラから放たれたレイの軌跡情報
	t_trajectory	trajectory;

	init_camera(&world.camera);
	gaze_ray.coordinates_vec = world.camera.coordinates_vec;
	// カメラが中にいるオブジェクトの屈折率をリストに追加する (何もない場合はglobalの屈折率)
	if (trajectory_init(&trajectory, world) != 0)
		return (1);
	//trajectory.refractive_indexs = NULL;
	//ft_lstadd_front(&trajectory.refractive_indexs, ft_lstnew(&world.scene_wide_object.material.refractive_index));
	//gaze_ray.prev_refractive_index = world.global_refraction_index;
	in_screen.y = 0;
	while (in_screen.y < HEIGHT - 1)
	{
		in_screen.x = 0;
		while (in_screen.x < WIDTH - 1)
		{
			// スクリーン上の点の3次元空間における位置ベクトルを計算
			gaze_ray.orientation_vec = get_rays_orientation_vector(in_screen, world.camera);
			//t_vector screen_vec;
			//screen_vec.y = 1.0 - 2 * in_screen.y / HEIGHT;
			//screen_vec.x = 2 * in_screen.x / WIDTH - 1.0;
			//screen_vec.z = 0;
			//gaze_ray.orientation_vec = normalize_vector(subst_vector(screen_vec, world.camera.coordinates_vec));
			color = ray_trace(world, &trajectory, gaze_ray);
			my_pixel_put(in_screen.x, in_screen.y, world.mlx.img, rgb_to_colorcode(color));
			in_screen.x++;
		}
		in_screen.y++;
	}
	free(trajectory.objects_trajectory);
	//ft_lstclear(&trajectory.refractive_indexs, NULL);
	return (0);
}

//void	debug_printer(t_xy in_screen, t_world world, t_intersection i, t_ray ray)
//{
//	t_object	debug;
//	t_coef		coef;
//	double		intersec_debug1;
//	double		intersec_debug2;
//	double		intersec1;
//	double		intersec2;

//	debug.coordinates_vec = world.light.coordinates_vec;
//	debug.orientation_vec = normalize_vector(subst_vector(world.light.coordinates_vec, debug.coordinates_vec));
//	debug.diameter = 0.1;
//	debug.height = 100;
//	calculate_cylinder_intersections_num(&coef, debug, camera.coordinates_vec, dir_vec);
//	intersec1 = ((-1 * cy_coef.b) - sqrt(cy_coef.d)) / (2 * cy_coef.a);
//	intersec2 = ((-1 * cy_coef.b) + sqrt(cy_coef.d)) / (2 * cy_coef.a);
//	if (intersec1 > intersec2)
//		swap_double(&intersec1, &intersec2);
//	intersec_debug1 = ((-1 * coef.b) - sqrt(coef.d)) / (2 * coef.a);
//	intersec_debug2 = ((-1 * coef.b) + sqrt(coef.d)) / (2 * coef.a);
//	if (intersec_debug1 > intersec_debug2)
//		swap_double(&intersec_debug1, &intersec_debug2);
//	if (coef.d >= 0 && (cy_coef.d < 0 || (is_intersection_in_object_height_range(object, add_vector(camera.coordinates_vec,
//		multi_vector(dir_vec, intersec1))) == true && intersec_debug1 <= intersec1)
//		|| (is_intersection_in_object_height_range(object, add_vector(camera.coordinates_vec,
//		multi_vector(dir_vec, intersec1))) == false && intersec_debug1 <= intersec2)
//		||  (is_intersection_in_object_height_range(object, add_vector(camera.coordinates_vec,
//			multi_vector(dir_vec, intersec1))) == false && is_intersection_in_object_height_range(object, add_vector(camera.coordinates_vec,
//				multi_vector(dir_vec, intersec2))) == false)))
//		my_pixel_put(in_screen.x, in_screen.y, mlx.img, 0xFF00FF);
//}
