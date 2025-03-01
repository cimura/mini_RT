#include "draw.h"
#include "ft_mlx.h"
#include "vector.h"

/*	de:	視線ベクトル
	pe: 視線位置
	pc:	球の中心
	pw: スクリーンの位置
	d_light: 光源ベクトル
	n: ノーマルベクトル
	p_i: 視線と球の交点
	p_l: 点光源の位置
	𝑅𝑎：環境光の反射光の放射輝度
	𝑅𝑑：直接光の拡散反射光の放射輝度
	𝑅𝑠：直接光の鏡面反射光の放射輝度
*/

/*
	𝑅𝑠=𝑘𝑠𝐼𝑖(𝐯⃗ ⋅𝐫⃗ )𝛼
	𝑘𝑠：鏡面反射係数
	𝐼𝑖：光源の光の強度
	𝐯⃗ ：視線ベクトルの逆ベクトル(∣∣𝐯⃗ ∣∣=1)
	𝐫⃗ ：入射光の正反射ベクトル(∣∣𝐫⃗ ∣∣=1)
	𝛼：光沢度(1≤𝛼)
*/

// RGB 計算しやすく0.0~1.0の範囲で表す
typedef struct	s_rgb
{
	__int32_t	red;
	__int32_t	green;
	__int32_t	blue;
}	t_rgb;

// カメラ Camera
typedef struct	s_camera
{
	char		*identifier;
	// 座標 ( x,y,z )
	t_vector	coordinates_vec;
	// 3D正規化方向ベクトル 範囲は[-1,1] ( x,y,z )
	t_vector	orientation_vec;// 3d normalized_orientation vector
	// FOV 水平方向の視野角 範囲は[0,180]
	int			horizontal_fov;
}	t_camera;

// 円柱 Cylinder
typedef struct	s_cylinder
{
	char		*identifier;
	// 座標 (x,y,z)
	t_vector	coordinates_vec;
	// 円柱の軸の三次元正規化ベクトル 範囲は[-1,1] (x,y,z)
	t_vector	orientation_vec;//  3d normalized vector of axis of cylinder
	// 直径
	double		diameter;
	// 高さ
	double		height;
	// RGB 範囲は0.0-1.0
	t_rgb		rgb;
}	t_cylinder;



double	calculate_intersection(t_vector pe, t_vector pc, t_vector de)
{
	t_vector v_tmp = subst_vector(pe, pc);
	double A = abst_squared(de);
	double B = 2 * inner_product(de, v_tmp);
	double C = abst_squared(v_tmp) - R * R;
	double D = B * B - 4 * A * C;

	double	t;

	if (D == 0)
		t = -B / (2 * A);
	else if (D > 0)
	{
		double answer1 = (-B - sqrt(D)) / (2 * A);
		double answer2 = (-B + sqrt(D)) / (2 * A);
		if (answer1 > 0)
			t = answer1;
		else
			t = answer2;
	}
	else
		t = -1;
	return (t);
}

t_vector calculate_normal(t_vector p_i, t_vector pc)
{
	t_vector n_tmp = subst_vector(p_i, pc);
	return multi_vector(n_tmp, 1 / sqrt(abst_squared(n_tmp)));
}

double calculate_lighting(t_color color, t_vector de, t_vector n, t_vector l)
{
	double R_a = color.constant.k_a * color.constant.I_a;
	double R_d = color.constant.k_d * color.constant.I_i * inner_product(n, l);
	if (inner_product(n, l) < 0)
		R_d = 0;
	double R_s = calculate_mirror_reflection(color.constant, de, n, l);

	return R_a + R_d + R_s;
}

// void render_pixel(int xs, int ys, t_cylinder cylinder, t_vector d_light, t_vector pw, t_mlx mlx)
// {
// 	t_vector pe, de, p_i, n, l, best_pc;
// 	set(&pe, 0, 0, -5);

// 	de = subst_vector(pw, pe);

// 	if (min_t != INFINITY)
// 	{
// 		// printf("min_t: %f\n", min_t);
// 		p_i = add_vector(pe, multi_vector(de, min_t));
// 		n = calculate_normal(p_i, best_pc);
// 		t_vector l_tmp = subst_vector(d_light, p_i);
// 		l = multi_vector(l_tmp, 1 / sqrt(abst_squared(l_tmp)));

// 		red.R_r = calculate_lighting(red, de, n, l);
// 		green.R_r = calculate_lighting(green, de, n, l);
// 		blue.R_r = calculate_lighting(blue, de, n, l);

// 		my_pixel_put(xs, ys, mlx.img, map(red, green, blue));
// 	}
// 	else
// 		my_pixel_put(xs, ys, mlx.img, 0x303030);
// }


void render_pixel(int xs, int ys, t_cylinder cylinder, t_vector d_light, t_vector pw, t_mlx mlx, t_camera camera)
{
	// t_vector de, p_i, n, l;
	(void)xs;
	(void)ys;
	(void)d_light;
	(void)pw;
	(void)mlx;

	double	A, B, C, D;

	A = pow(camera.orientation_vec.x, 2) + pow(camera.orientation_vec.z, 2);
	B = 2 * (camera.orientation_vec.x * (camera.coordinates_vec.x - cylinder.coordinates_vec.x)
		 + camera.orientation_vec.z * (camera.coordinates_vec.z - cylinder.coordinates_vec.z));
	C = (pow((camera.coordinates_vec.x - cylinder.coordinates_vec.x), 2) + pow((camera.coordinates_vec.z - cylinder.coordinates_vec.z), 2)) - pow(cylinder.diameter / 2, 2);

	D = pow(B, 2) - 4 * A * C;
	if (D > 0)
		my_pixel_put(xs, ys, mlx.img, 0xFF0000);
	//printf("%lf ", D);
}


void render_scene(t_mlx mlx, t_cylinder cylinder, t_vector d_light, t_camera camera)
{
	t_vector	pw;
	double xs, ys;
	double xw, yw;
	for (ys = 0; ys < HEIGHT; ys++)
	{
		yw = (-2 * ys) / (HEIGHT - 1) + 1.0;
		for (xs = 0; xs < WIDTH; xs++)
		{
			xw = (2 * xs) / (WIDTH - 1) - 1.0;
			set(&pw, xw, yw, 0);
			render_pixel(xs, ys, cylinder, d_light, pw, mlx, camera);
		}
		//printf("\n");
	}
}

// void	init_color(t_color *color, double value, double k_a, double k_d, double k_s, double I_a, double I_i)
// {
// 	color->value = value;
// 	color->constant.k_a = k_a;
// 	color->constant.k_d = k_d;
// 	color->constant.k_s = k_s;
// 	color->constant.I_a = I_a;
// 	color->constant.I_i = I_i;
// }

int	main() {
	t_mlx	mlx;
	init(&mlx);

	t_cylinder	cylinder;
	cylinder.height = 2.0;
	cylinder.diameter = 2.0;
	set(&cylinder.coordinates_vec, 0, 0, 5);
	set(&cylinder.orientation_vec, 0, 0, 0);
	cylinder.rgb.red = 200;
	cylinder.rgb.green = 255;
	cylinder.rgb.blue = 168;

	t_vector	d_light;
	d_light.x = 0;
	d_light.y = 5;
	d_light.z = -5;
	t_camera	camera;
	set(&camera.coordinates_vec, 0, 0, 10);
	set(&camera.orientation_vec, 0, 0, -1);

	render_scene(mlx, cylinder, d_light, camera);

	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->ptr, 0, 0);
	mlx_loop(mlx.ptr);
}
