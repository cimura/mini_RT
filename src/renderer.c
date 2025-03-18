#include "renderer.h"

//void	debug_printer(t_xy in_screen, t_world world, t_intersection i, t_ray ray)

static void render_pixel(t_world world, t_xy in_screen, t_ray gaze_ray)
{
	int				color;
	t_intersection	closest_intersection;

	closest_intersection = find_intersection_minimum_distance(world, gaze_ray);
	// 交点がない場合は背景色を置いてreturn  余分な計算を省くことができる
	 if (closest_intersection.t < 0)
	 {
	 	my_pixel_put(in_screen.x, in_screen.y, world.mlx.img, BACKGROUND_COLOR);
	 	return ;
	 }
	calculate_intersections_normal_vector(&closest_intersection, gaze_ray);
	color = calculate_pixel_color(world, closest_intersection, gaze_ray);
	my_pixel_put(in_screen.x, in_screen.y, world.mlx.img, color);
	// Debug
	//debug_printer(xs, ys, coef, object, light, dir_vec, mlx, camera);
}

static void	set_screen_normalized_basis_vectors(t_camera camera, t_vector *basisx, t_vector *basisy)
{
	// 今回はカメラの回転は指定されないので、x軸に水平でy軸に平行な角度
	// x
	basisx->y = 0;
	basisx->x = camera.orientation_vec.z
		/ sqrt(pow(camera.orientation_vec.z, 2)
		+ pow(camera.orientation_vec.x, 2));
	basisx->z = -1 * camera.orientation_vec.x
		/ sqrt(pow(camera.orientation_vec.x, 2)
		+ pow(camera.orientation_vec.z, 2));
	// y
	*basisy = cross_product(camera.orientation_vec, *basisx);
}

static t_vector	get_rays_orientation_vector(t_xy in_screen, t_vector center_of_screen, t_vector basis_x, t_vector basis_y)
{
	t_vector	orientation_vec;
	t_vector	coordinates_in_screen_basis;

	coordinates_in_screen_basis = add_vector(multi_vector(basis_x, 2 * in_screen.x / WIDTH - SCREEN_WIDTH / 2),
		multi_vector(basis_y, SCREEN_HEIGHT / 2 - 2 * in_screen.y/ HEIGHT)); 
	orientation_vec = add_vector(center_of_screen, coordinates_in_screen_basis);
	return (normalize_vector(orientation_vec));
}


// いったんカメラの位置ベクトル、方向ベクトル、FOV（視野角）を固定する（原点上のx,yにスクリーンを張る）
void render_scene(t_world world)
{
	// スクリーンの位置ベクトル
	//t_vector	screen_vec;
	// カメラから2次元スクリーン上の任意の点(x,y)の方向ベクトル
	t_ray		gaze_ray;
	// 2次元スクリーン上のxs,ys
	t_xy		in_screen;
	// 3次元ワールド上のxw,yw
	//t_vector	in_world;
	// スクリーンの中心の位置
	t_vector	center_of_screen;
	// スクリーン上の正規化直交基底ベクトル
	t_vector	screen_basis_x;
	t_vector	screen_basis_y;

	set_screen_normalized_basis_vectors(world.camera, &screen_basis_x, &screen_basis_y);
	center_of_screen = multi_vector(world.camera.orientation_vec, (SCREEN_WIDTH / 2)
	* (1 / tan(world.camera.horizontal_fov / 2 * (M_PI / 180))));
	printf("center_of_screen(%lf,%lf,%lf)\n", center_of_screen.x, center_of_screen.y, center_of_screen.z);
	gaze_ray.coordinates_vec = world.camera.coordinates_vec;
	in_screen.y = 0;
	while (in_screen.y < HEIGHT - 1)
	{
		in_screen.x = 0;
		while (in_screen.x < WIDTH - 1)
		{
			// スクリーン上の点の3次元空間における位置ベクトルを計算
			//in_world.y = 1.0 - 2 * in_screen.y / HEIGHT;
			//in_world.x = 2 * in_screen.x / WIDTH - 1.0;
			//set(&screen_vec, in_world.x, in_world.y, 0);
			//gaze_ray.orientation_vec = normalize_vector(subst_vector(screen_vec, world.camera.coordinates_vec));
			gaze_ray.orientation_vec = get_rays_orientation_vector(in_screen, center_of_screen, screen_basis_x, screen_basis_y);
			render_pixel(world, in_screen, gaze_ray);
			in_screen.x++;
		}
		in_screen.y++;
	}
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
