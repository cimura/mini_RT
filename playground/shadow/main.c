#include "draw.h"
#include "ft_mlx.h"
#include "vector.h"
#include "minirt.h"
#include "light.h"

void	put_color_on_intersection_pixel(int xs, int ys, t_plane plane, t_light light, t_vector dir_vec, t_mlx mlx, t_camera camera, t_ambient_lightning ambient_lightning)
{
	double	t;
	int		color_value;
	t_vector	intersection_point;
	//t_vector	incidence_vec;

	//t_vector	reflection_vec;
	//t_vector	inverse_camera_orientation_vec;
	//	// 視線逆ベクトルと正反射ベクトルの内積
	//double				inverse_dot_reflection;
	//double				normal_dot_incindence;

	//	// 物体の表面の色によって変える
	//t_light_ratio		ambient_coefficient;
	//t_light_ratio		diffuse_coefficient;
	//t_light_ratio		specular_coefficient;

	//	// 光の色によって変える
	//t_light_ratio		ambient_light;
	//t_light_ratio		diffuse_light;
	//t_light_ratio		specular_light;
	//t_light_ratio		result_color;

	if (calculate_inner_product(dir_vec, plane.orientation_vec) == 0)
	{
		my_pixel_put(xs, ys, mlx.img, BACKGROUND_COLOR);
		return ;
	}

	t = -(calculate_inner_product(subst_vector(camera.coordinates_vec, plane.coordinates_vec), plane.orientation_vec)
			/ calculate_inner_product(dir_vec, plane.orientation_vec));

	// printf("%f ", t);
	// 交点があるなら
	if (t > 0)
	{
		// 交点 P = s + t * d
        intersection_point.x = camera.coordinates_vec.x + t * dir_vec.x;
        intersection_point.y = camera.coordinates_vec.y + t * dir_vec.y;
        intersection_point.z = camera.coordinates_vec.z + t * dir_vec.z;

		//incidence_vec = normalize_vector(subst_vector(light.coordinates_vec, intersection_point));
		//normal_dot_incindence = calculate_inner_product(plane.orientation_vec, incidence_vec);
		//if (normal_dot_incindence < 0.0)
		//	normal_dot_incindence = 0.0;
		//if (normal_dot_incindence > 1.0)
		//	normal_dot_incindence = 1.0;

		//reflection_vec = subst_vector(multi_vector(plane.orientation_vec, 2 * normal_dot_incindence), incidence_vec);
		//inverse_camera_orientation_vec = normalize_vector(multi_vector(dir_vec, -1));
		//inverse_dot_reflection = calculate_inner_product(inverse_camera_orientation_vec, reflection_vec);
		//if (inverse_dot_reflection < 0.0)
		//	inverse_dot_reflection = 0.0;
		//if (inverse_dot_reflection > 1.0)
		//	inverse_dot_reflection = 1.0;

		//set_light_ratio(&ambient_coefficient, plane.rgb, AMBIENT_COEFFICIENT);
		//set_light_ratio(&ambient_light, ambient_lightning.rgb, ambient_lightning.ratio);
		//ambient_light = multi_light_ratio(ambient_light, ambient_coefficient);
		//set_light_ratio(&diffuse_coefficient, plane.rgb, DIFFUSE_COEFFICIENT);
		//set_light_ratio(&diffuse_light, light.rgb, light.ratio * normal_dot_incindence);
		//diffuse_light = multi_light_ratio(diffuse_light, diffuse_coefficient);
		//set_light_ratio(&specular_coefficient, plane.rgb, SPECULAR_COEFFICIENT);
		//set_light_ratio(&specular_light, light.rgb, light.ratio * pow(inverse_dot_reflection, SHININESS));
		//specular_light = multi_light_ratio(specular_light, specular_coefficient);
		//result_color = add_light_ratio(ambient_light, diffuse_light);
		//result_color = add_light_ratio(result_color, specular_light);

		//color_value = rgb_to_colorcode(result_color);
		//// printf("%d ", color_value);
		color_value = calculate_color(light, (t_object *)&plane, dir_vec, ambient_lightning, intersection_point);
		my_pixel_put(xs, ys, mlx.img, color_value);
	}
	else
		my_pixel_put(xs, ys, mlx.img, BACKGROUND_COLOR);
}

// いったんカメラの位置ベクトル、方向ベクトル、FOV（視野角）を固定する（原点上のx,yにスクリーンを張る）
void render_scene(t_mlx mlx, t_plane plane, t_light light, t_camera camera, t_ambient_lightning ambient_lightning)
{
	// スクリーンの位置ベクトル
	t_vector	screen_vec;
	// カメラから2次元スクリーン上の任意の点(x,y)の方向ベクトル
	t_vector	dir_vec;
	// 2次元スクリーン上のxs,ys
	double xs, ys;
	// 3次元ワールド上のxw,yw
	double xw, yw;

	ys = 0;
	while (ys < HEIGHT - 1)
	{
		xs = 0;
		while (xs < WIDTH - 1)
		{
			// スクリーン上の点の3次元空間における位置ベクトルを計算
			yw = 1.0 - 2 * ys / HEIGHT;
			xw = 1.0 - 2 * xs / WIDTH;
			set(&screen_vec, xw, yw, 0);
			// ray = s + tdの d, sはカメラベクトル
			dir_vec = normalize_vector(subst_vector(screen_vec, camera.coordinates_vec));
			//render_pixel(xs, ys, plane, light, dir_vec, mlx, camera, ambient_lightning);
			put_color_on_intersection_pixel(xs, ys, plane, light, dir_vec, mlx, camera, ambient_lightning);
			xs++;
		}
		//printf("\n");
		ys++;
	}
}

int	main() {
	t_mlx	mlx;
	init(&mlx);

	t_world	world;
	t_plane	plane;
	set(&plane.coordinates_vec, 0, -1, 0);
	set(&plane.orientation_vec, 0, 1, 0);
	plane.rgb.red = 0;
	plane.rgb.green = 246;
	plane.rgb.blue = 246;

	t_list	*new_node = ft_lstnew(&plane);
	ft_lstadd_back(&world.objects, new_node);

	t_ambient_lightning	ambient_lightning;
	ambient_lightning.ratio = 0.2;
	ambient_lightning.rgb.red = 222;
	ambient_lightning.rgb.green = 185;
	ambient_lightning.rgb.blue = 155;

	t_light	light;
	set(&light.coordinates_vec, 0, 0.9, 2.5);
	light.ratio = 1;
	light.rgb.red = 255;
	light.rgb.green = 255;
	light.rgb.blue = 255;


	t_camera	camera;
	set(&camera.coordinates_vec, 0, 0, -10);
	set(&camera.orientation_vec, 0, 0, 0);

	render_scene(mlx, plane, light, camera, ambient_lightning);

	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->ptr, 0, 0);
	mlx_loop(mlx.ptr);
}
