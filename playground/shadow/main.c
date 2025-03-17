#include "draw.h"
#include "ft_mlx.h"
#include "vector.h"
#include "minirt.h"
#include "light.h"

void	initializer(t_world *world)
{
	t_mlx	mlx;
	init(&mlx);
	world->mlx = mlx;

	t_ambient_lightning	ambient_lightning;
	ambient_lightning.ratio = 0.2;
	ambient_lightning.rgb.red = 222;
	ambient_lightning.rgb.green = 185;
	ambient_lightning.rgb.blue = 155;
	world->ambient_lightning = ambient_lightning;

	t_light	light;
	set(&light.coordinates_vec, 0, 0.9, 2.5);
	light.ratio = 1;
	light.rgb.red = 255;
	light.rgb.green = 255;
	light.rgb.blue = 255;
	world->light = light;

	t_camera	camera;
	set(&camera.coordinates_vec, 0, 0, -10);
	set(&camera.orientation_vec, 0, 0, 0);
	world->camera = camera;
}

void	put_color_on_intersection_pixel(int xs, int ys, t_object object, t_world world, t_vector dir_vec)
{
	double	t;
	int		color_value;
	t_vector	intersection_point;
	if (calculate_inner_product(dir_vec, object.orientation_vec) == 0)
	{
		my_pixel_put(xs, ys, world.mlx.img, BACKGROUND_COLOR);
		return ;
	}

	t = -(calculate_inner_product(subst_vector(world.camera.coordinates_vec, object.coordinates_vec), object.orientation_vec)
			/ calculate_inner_product(dir_vec, object.orientation_vec));

	// printf("%f ", t);
	// 交点があるなら
	if (t > 0)
	{
		// 交点 P = s + t * d
        intersection_point.x = world.camera.coordinates_vec.x + t * dir_vec.x;
        intersection_point.y = world.camera.coordinates_vec.y + t * dir_vec.y;
        intersection_point.z = world.camera.coordinates_vec.z + t * dir_vec.z;

		color_value = calculate_color(world.light, &object, dir_vec, world.ambient_lightning, intersection_point);
		my_pixel_put(xs, ys, world.mlx.img, color_value);
	}
	else
		my_pixel_put(xs, ys, world.mlx.img, BACKGROUND_COLOR);
}

// いったんカメラの位置ベクトル、方向ベクトル、FOV（視野角）を固定する（原点上のx,yにスクリーンを張る）
void render_scene(t_world world, t_object object)
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
			dir_vec = normalize_vector(subst_vector(screen_vec, world.camera.coordinates_vec));
			put_color_on_intersection_pixel(xs, ys, object, world, dir_vec);
			xs++;
		}
		//printf("\n");
		ys++;
	}
}

int	main() {
	t_world	world;
	initializer(&world);

	t_object	plane;
	set(&plane.coordinates_vec, 0, -1, 0);
	set(&plane.orientation_vec, 0, 1, 0);
	plane.rgb.red = 0;
	plane.rgb.green = 246;
	plane.rgb.blue = 246;

	render_scene(world, plane);

	mlx_put_image_to_window(world.mlx.ptr, world.mlx.win_ptr, world.mlx.img->ptr, 0, 0);
	mlx_loop(world.mlx.ptr);
}
