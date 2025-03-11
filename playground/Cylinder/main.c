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
	double	red;
	double	green;
	double	blue;
}	t_rgb;

typedef struct	s_light_ratio
{
	double	red;
	double	green;
	double	blue;
}	t_light_ratio;

// 環境光 Ambient lightning
typedef struct	s_ambient_lightning
{
	char	*identifier;
	// 環境光の比率 ambient_lightning_ratio 範囲は[0.0-1.0]
	double	ratio;
	// RGB 範囲は0.0-1.0 ( red,green,blue )
	t_rgb	rgb;
}	t_ambient_lightning;

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

// 光源 Light
typedef struct	s_light
{
	char		*identifier;
	// 座標 ( x,y,z )
	t_vector	coordinates_vec;
	// 光の明るさ比率 範囲は[0.0,1.0]
	double		ratio;
	// ※mandatoryでは不使用 RGB 範囲は0.0-1.0
	t_rgb		rgb;
}	t_light;

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

typedef struct s_coef
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_coef;


// 諸々の定数を定義しておく あとで全体の構造体に入れる
// 環境光反射係数
#define	AMBIENT_COEFFICIENT 0.01
// 拡散反射光反射係数
#define	DIFFUSE_COEFFICIENT 0.69
// 鏡面反射係数
#define SPECULAR_COEFFICIENT 0.5
// 光沢度
#define SHININESS 8

// 背景色
#define BACKGROUND_COLOR 0xaaaaaa

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

// 交点が手前か奥側かの判定 法線ベクトルの向きを左右する
#define I1 1
#define I2 2

// 視線と円柱の表面の法線ベクトルを計算する (円柱データ、交点、円柱の底面の位置ベクトル)
t_vector	calculate_cylinder_normal_vector(t_cylinder cylinder, t_vector intersection,
		t_vector base, int dir_flag)
{
	t_vector	normal_vector;
	t_vector	base_to_intersection;
	double		bti_dot_orientation;

	base_to_intersection = subst_vector(intersection, base);
	bti_dot_orientation = dot_vector(base_to_intersection, cylinder.orientation_vec);
	if (dir_flag == I1)
		normal_vector = subst_vector(base_to_intersection, multi_vector(cylinder.orientation_vec,
			bti_dot_orientation));
	else
		normal_vector = subst_vector(multi_vector(cylinder.orientation_vec, bti_dot_orientation),
			base_to_intersection);
	normal_vector = normalize_vector(normal_vector);
	return (normal_vector);
}

void	set_light_ratio(t_light_ratio *light, t_rgb rgb, double coefficient)
{
	light->red = rgb.red / 255 * coefficient;
	light->green = rgb.green /255 * coefficient;
	light->blue = rgb.blue / 255 * coefficient;
}

t_light_ratio	add_light_ratio(t_light_ratio l1, t_light_ratio l2)
{
	t_light_ratio	result;

	result.red = l1.red + l2.red;
	if (result.red > 1.0)
		result.red = 1.0;
	result.green = l1.green + l2.green;
	if (result.green > 1.0)
		result.green = 1.0;
	result.blue = l1.blue + l2.blue;
	if (result.blue > 1.0)
		result.blue = 1.0;
	return (result);
}

t_light_ratio	multi_light_ratio(t_light_ratio l1, t_light_ratio l2)
{
	t_light_ratio	result;

	result.red = l1.red * l2.red;
	result.green = l1.green * l2.green;
	result.blue = l1.blue * l2.blue;
	return (result);
}

int	rgb_to_colorcode(t_light_ratio light)
{
	int	result;

	// result = red.value*red.R_r * pow(16, 4) + green.value*green.R_r * pow(16, 2) + blue.value*blue.R_r;
		result = (int)(light.red * 255) << 16  // 赤は上位16ビット
		   | (int)(light.green * 255) << 8  // 緑は中間8ビット
		   | (int)(light.blue * 255);  // 青は下位8ビット
	return (result);
}

// 交点があったピクセルの色を計算する
int	calculate_intersections_color(t_cylinder cylinder, t_light light, t_vector dir_vec, t_ambient_lightning ambient_lightning, t_vector normal_vec, t_vector intersection_vec)
{
	t_vector			incidence_vec;
	double				normal_dot_incindence;
	// 光源の正反射ベクトル
	t_vector			reflection_vec;
	// 視線ベクトルの逆ベクトル
	t_vector			inverse_camera_orientation_vec;
	// 視線逆ベクトルと正反射ベクトルの内積
	double				inverse_dot_reflection;
	// 物体の表面の色によって変える
	t_light_ratio		ambient_coefficient;
	t_light_ratio		diffuse_coefficient;
	t_light_ratio		specular_coefficient;
	// 光の色によって変える
	t_light_ratio		ambient_light;
	t_light_ratio		diffuse_light;
	t_light_ratio		specular_light;
	t_light_ratio		result_color;

	// 直接光の入射ベクトル
	incidence_vec = normalize_vector(subst_vector(light.coordinates_vec, intersection_vec));
	// 法線ベクトルと入射ベクトルの内積 これを0-1の範囲にする(負の値の時は光は当たらないため)
	normal_dot_incindence = dot_vector(normal_vec, incidence_vec);
	if (normal_dot_incindence < 0.0)
		normal_dot_incindence = 0.0;
	if (normal_dot_incindence > 1.0)
		normal_dot_incindence = 1.0;
	reflection_vec = subst_vector(multi_vector(normal_vec, 2 * normal_dot_incindence), incidence_vec);
	inverse_camera_orientation_vec = normalize_vector(multi_vector(dir_vec, -1));
	inverse_dot_reflection = dot_vector(inverse_camera_orientation_vec, reflection_vec);
	if (inverse_dot_reflection < 0.0)
		inverse_dot_reflection = 0.0;
	if (inverse_dot_reflection > 1.0)
		inverse_dot_reflection = 1.0;
	set_light_ratio(&ambient_coefficient, cylinder.rgb, AMBIENT_COEFFICIENT);
	set_light_ratio(&ambient_light, ambient_lightning.rgb, ambient_lightning.ratio);
	ambient_light = multi_light_ratio(ambient_light, ambient_coefficient);
	set_light_ratio(&diffuse_coefficient, cylinder.rgb, DIFFUSE_COEFFICIENT);
	set_light_ratio(&diffuse_light, light.rgb, light.ratio * normal_dot_incindence);
	diffuse_light = multi_light_ratio(diffuse_light, diffuse_coefficient);
	set_light_ratio(&specular_coefficient, cylinder.rgb, SPECULAR_COEFFICIENT);
	set_light_ratio(&specular_light, light.rgb, light.ratio * pow(inverse_dot_reflection, SHININESS));
	specular_light = multi_light_ratio(specular_light, specular_coefficient);
	result_color = add_light_ratio(ambient_light, diffuse_light);
	result_color = add_light_ratio(result_color, specular_light);
	return (rgb_to_colorcode(result_color));
}

double	a_coef(t_vector dir_vec, double co_dot_dir, double co_dot_co)
{
	double	dir_dot_dir;

	dir_dot_dir = dot_vector(dir_vec, dir_vec);
	return (dir_dot_dir - pow(co_dot_dir, 2) / co_dot_co);
}

double	b_coef(double co_dot_dir, double dir_dot_ctc, double co_dot_ctc, double co_dot_co)
{
	return (2.0 * (dir_dot_ctc - co_dot_dir * co_dot_ctc / co_dot_co));
}

double	c_coef(t_vector camera_to_cylinder, t_cylinder cylinder, double co_dot_ctc, double co_dot_co)
{
	double	ctc_dot_ctc;

	ctc_dot_ctc = dot_vector(camera_to_cylinder, camera_to_cylinder);
	return (ctc_dot_ctc - pow(co_dot_ctc, 2) / co_dot_co - pow(cylinder.diameter / 2, 2));
}

void	calculate_intersections_num(t_coef *coef, t_cylinder cylinder, t_camera camera, t_vector dir_vec)
{
	t_vector	camera_to_cylinder;
	double		co_dot_dir;
	double		co_dot_co;
	double		dir_dot_ctc;
	double		co_dot_ctc;

	camera_to_cylinder = subst_vector(camera.coordinates_vec, cylinder.coordinates_vec);
	co_dot_dir = dot_vector(cylinder.orientation_vec, dir_vec);
	co_dot_co = dot_vector(cylinder.orientation_vec, cylinder.orientation_vec);
	dir_dot_ctc = dot_vector(dir_vec, camera_to_cylinder);
	co_dot_ctc = dot_vector(cylinder.orientation_vec, camera_to_cylinder);
	coef->a = a_coef(dir_vec, co_dot_dir, co_dot_co);
	coef->b = b_coef(co_dot_dir, dir_dot_ctc, co_dot_ctc, co_dot_co);
	coef->c = c_coef(camera_to_cylinder, cylinder, co_dot_ctc, co_dot_co);
	coef->d = pow(coef->b, 2) - 4 * coef->a * coef->c;
}

void	put_color_on_intersection_pixel(int xs, int ys, t_cylinder cylinder, t_light light, t_vector dir_vec, t_mlx mlx, t_camera camera, t_ambient_lightning ambient_lightning, t_coef coef)
{
	t_vector	intersec1;
	t_vector	intersec2;
	t_vector	cylinder_bottom_vec;
	double		i1_dot_co;
	double		i2_dot_co;

	intersec1 = add_vector(camera.coordinates_vec,
		multi_vector(dir_vec, ((-1 * coef.b) - sqrt(coef.d)) / (2 * coef.a)));
	intersec2 = add_vector(camera.coordinates_vec,
		multi_vector(dir_vec, ((-1 * coef.b) + sqrt(coef.d)) / (2 * coef.a)));
	cylinder_bottom_vec = subst_vector(cylinder.coordinates_vec,
		multi_vector(cylinder.orientation_vec, cylinder.height / 2));
	i1_dot_co = dot_vector(subst_vector(intersec1, cylinder_bottom_vec), cylinder.orientation_vec);
	i2_dot_co = dot_vector(subst_vector(intersec2, cylinder_bottom_vec), cylinder.orientation_vec);
	if (i1_dot_co >= 0 && i1_dot_co <= cylinder.height)
	{
		my_pixel_put(xs, ys, mlx.img, calculate_intersections_color(cylinder, light, dir_vec, ambient_lightning,
			calculate_cylinder_normal_vector(cylinder, intersec1, cylinder_bottom_vec, I1), intersec1));
	}
	else if (i2_dot_co >= 0 && i2_dot_co <= cylinder.height)
	{
		my_pixel_put(xs, ys, mlx.img, calculate_intersections_color(cylinder, light, dir_vec, ambient_lightning,
			calculate_cylinder_normal_vector(cylinder, intersec2, cylinder_bottom_vec, I2), intersec2));
	}
	else
		my_pixel_put(xs, ys, mlx.img, BACKGROUND_COLOR);
}

void render_pixel(int xs, int ys, t_cylinder cylinder, t_light light, t_vector dir_vec, t_mlx mlx, t_camera camera, t_ambient_lightning ambient_lightning)
{
	// t_vector de, p_i, n, l;

	// At^2 + Bt + C = 0 判別式D 交わるときのt二つT1,T2 交点のy座標二つPy1,Py2
	// double	A, B, C, D, T1, T2/*, Py1, Py2*/;
	// 円柱の中心のy座標 - 交点のy座標二つ H1, H2
	//double H1, H2;

	//A = pow(dir_vec.x, 2) + pow(dir_vec.z, 2);
	//B = 2 * (dir_vec.x * (camera.coordinates_vec.x - cylinder.coordinates_vec.x)
	//	 + dir_vec.z * (camera.coordinates_vec.z - cylinder.coordinates_vec.z));
	//C = (pow((camera.coordinates_vec.x - cylinder.coordinates_vec.x), 2) + pow((camera.coordinates_vec.z - cylinder.coordinates_vec.z), 2)) - pow(cylinder.diameter / 2, 2);

	//D = pow(B, 2) - 4 * A * C;
	
	// d: 円柱の軸の方向ベクトル  D: 視線の方向ベクトル  O: カメラの位置ベクトル  C: 円柱の位置ベクトル
	// t_vector	camera_to_cylinder = subst_vector(camera.coordinates_vec, cylinder.coordinates_vec);
	// double	D_dot_D = dot_vector(dir_vec, dir_vec);
	// double	d_dot_D = dot_vector(cylinder.orientation_vec, dir_vec);
	// double	d_dot_d = dot_vector(cylinder.orientation_vec, cylinder.orientation_vec);
	// double	D_dot_OC = dot_vector(dir_vec, camera_to_cylinder);
	// double	d_dot_OC = dot_vector(cylinder.orientation_vec, camera_to_cylinder);
	// double	OC_dot_OC = dot_vector(camera_to_cylinder, camera_to_cylinder);

	// A = D_dot_D - pow(d_dot_D, 2) / d_dot_d;
	// B = 2.0 * (D_dot_OC - d_dot_D * d_dot_OC / d_dot_d);
	// C = OC_dot_OC - pow(d_dot_OC, 2) / d_dot_d - pow(cylinder.diameter / 2, 2);

	// 判別式
	// D = pow(B, 2) - 4 * A * C;
	t_coef	coef;
	calculate_intersections_num(&coef, cylinder, camera, dir_vec);

	//printf("%lf ", d_dot_d);

	// 交点がない場合は背景色を置いてreturn
	if (coef.d < 0)
	{
		my_pixel_put(xs, ys, mlx.img, BACKGROUND_COLOR);
		return ;
	}
	put_color_on_intersection_pixel(xs, ys, cylinder, light, dir_vec, mlx, camera, ambient_lightning, coef);

	// 交わるときの係数tを計算 P = s + td の t  (P:視線と物体の交点 s:カメラの位置ベクトル d:カメラの方向ベクトル)
	// t1 = ((-1 * coef.b) - sqrt(coef.d)) / (2 * coef.a);
	// t2 = ((-1 * coef.b) + sqrt(coef.d)) / (2 * coef.a);

// 交点がある場合
	// 交点のy座標を計算
	//Py1 = camera.coordinates_vec.y + T1 * dir_vec.y;
	//Py2 = camera.coordinates_vec.y + T2 * dir_vec.y;

	// 交点の位置ベクトルを計算 R1 R2は交点1, 2
	// t_vector	R1 = add_vector(camera.coordinates_vec, multi_vector(dir_vec, t1));
	// t_vector	R2 = add_vector(camera.coordinates_vec, multi_vector(dir_vec, t2));

	// 円柱の底面の座標2つ C0, C1
	// t_vector	C0 = subst_vector(cylinder.coordinates_vec, multi_vector(cylinder.orientation_vec, cylinder.height / 2));
	//t_vector	C1 = add_vector(cylinder.coordinates_vec, multi_vector(cylinder.orientation_vec, cylinder.height / 2));

	// 円柱の軸方向ベクトルと中心から交点へのベクトルの内積を計算
	// double	R1_dot_d = dot_vector(subst_vector(R1, C0), cylinder.orientation_vec);
	// double	R2_dot_d = dot_vector(subst_vector(R2, C0), cylinder.orientation_vec);

	// 交点と円柱の中心のy座標の差を計算
	//H1 = cylinder.coordinates_vec.y - Py1;
	//H2 = cylinder.coordinates_vec.y - Py2;
	//printf("%lf ", D);
	// 交点が円筒の高さ範囲内にあるかどうか
	//if (D >= 0 && ((H1 >= -1 * (cylinder.height / 2) && H1 <= cylinder.height / 2)
	//	|| (H2 >= -1 * (cylinder.height / 2) && H2 <= cylinder.height / 2)))
	//	my_pixel_put(xs, ys, mlx.img, 0xFF0000);
	//else
	//	my_pixel_put(xs, ys, mlx.img, 0x0000FF);

	// 視線と円柱の曲名との交点における法線ベクトル
	// t_vector	normal_vector;

	// 交点の円柱高さ範囲内チェック
	// if (R1_dot_d >= 0 && R1_dot_d <= cylinder.height)
	// {
	// 	normal_vector = calculate_cylinder_normal_vector(cylinder, R1, C0, I1);
	// 	my_pixel_put(xs, ys, mlx.img, calculate_intersections_color(cylinder, light, dir_vec, ambient_lightning, normal_vector, R1));
	// }
	// else if (R2_dot_d >= 0 && R2_dot_d <= cylinder.height)
	// {
	// 	normal_vector = calculate_cylinder_normal_vector(cylinder, R2, C0, I2);
	// 	my_pixel_put(xs, ys, mlx.img, calculate_intersections_color(cylinder, light, dir_vec, ambient_lightning, normal_vector, R2));
	// }
	// else
	// 	my_pixel_put(xs, ys, mlx.img, 0xaaaaaa);
}

// いったんカメラの位置ベクトル、方向ベクトル、FOV（視野角）を固定する（原点上のx,yにスクリーンを張る）
void render_scene(t_mlx mlx, t_cylinder cylinder, t_light light, t_camera camera, t_ambient_lightning ambient_lightning)
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
			dir_vec = normalize_vector(subst_vector(screen_vec, camera.coordinates_vec));
			render_pixel(xs, ys, cylinder, light, dir_vec, mlx, camera, ambient_lightning);
			xs++;
		}
		//printf("\n");
		ys++;
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
	set(&cylinder.orientation_vec, 1/sqrt(3), 1/sqrt(3), 1/sqrt(3));
	cylinder.rgb.red = 246;
	cylinder.rgb.green = 246;
	cylinder.rgb.blue = 38;

	t_ambient_lightning	ambient_lightning;
	ambient_lightning.ratio = 0.2;
	ambient_lightning.rgb.red = 222;
	ambient_lightning.rgb.green = 185;
	ambient_lightning.rgb.blue = 155;

	t_light	light;
	set(&light.coordinates_vec, -1, 8, 5);
	light.ratio = 0.6;
	light.rgb.red = 255;
	light.rgb.green = 255;
	light.rgb.blue = 255;

	t_camera	camera;
	set(&camera.coordinates_vec, 0, 0, -5);
	set(&camera.orientation_vec, 0, 0, 0);

	render_scene(mlx, cylinder, light, camera, ambient_lightning);

	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->ptr, 0, 0);
	mlx_loop(mlx.ptr);
}
