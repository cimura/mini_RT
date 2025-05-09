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

// 平面 Plane
typedef struct	s_plane
{
	char		*identifier;
	// 座標 (x,y,z)
	t_vector	coordinates_vec;
	// 平面の軸の三次元正規化法線ベクトル 範囲は[-1,1] (x,y,z)
	t_vector	orientation_vec;//  3d normalized vector of axis of cylinder
	// RGB 範囲は0.0-1.0
	t_rgb		rgb;
}	t_plane;

typedef struct s_coef
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_coefficient;

// レイ（視線）用の構造体
typedef struct	s_ray
{
	t_vector	coordinates_vec;
	t_vector	orientation_vec;
	double		len;
}	t_ray;


// 諸々の定数を定義しておく あとで全体の構造体に入れる
// 環境光反射係数
#define	AMBIENt_coefficientFICIENT 0.01
// 拡散反射光反射係数
#define	DIFFUSE_COEFFICIENT 0.69
// 鏡面反射係数
#define SPECULAR_COEFFICIENT 0.5
// 光沢度
#define SHININESS 8

// 背景色
#define BACKGROUND_COLOR 0xaaaaaa

t_vector calculate_normal(t_vector p_i, t_vector pc)
{
	t_vector n_tmp = subst_vector(p_i, pc);
	return multi_vector(n_tmp, 1 / sqrt(abst_squared(n_tmp)));
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

// 平面の方程式　ax + by + cz + d = 0
// 法線ベクトル　n (0, 0, -10)
// -> 1/√3(x - 0) + 1/√3(y - 0) + 1/√3(z + 10) = 0
// -> 1/√3x + 1/√3y + 1/√3z + 10/√3 = 0

void	put_color_on_intersection_pixel(int xs, int ys, t_plane plane, t_light light, t_vector dir_vec, t_mlx mlx, t_camera camera, t_ambient_lightning ambient_lightning)
{
	double	t;
	int		color_value;
	t_vector	intersection_point;
	t_vector	incidence_vec;

	t_vector	reflection_vec;
	t_vector	inverse_camera_orientation_vec;
		// 視線逆ベクトルと正反射ベクトルの内積
	double				inverse_dot_reflection;
	double				normal_dot_incindence;

		// 物体の表面の色によって変える
	t_light_ratio		ambient_coefficientficient;
	t_light_ratio		diffuse_coefficient;
	t_light_ratio		specular_coefficient;

		// 光の色によって変える
	t_light_ratio		ambient_light;
	t_light_ratio		diffuse_light;
	t_light_ratio		specular_light;
	t_light_ratio		result_color;

	if (inner_product(dir_vec, plane.orientation_vec) == 0)
	{
		my_pixel_put(xs, ys, mlx.img, BACKGROUND_COLOR);
		return ;
	}

	t = -(inner_product(subst_vector(camera.coordinates_vec, plane.coordinates_vec), plane.orientation_vec)
			/ inner_product(dir_vec, plane.orientation_vec));

	// printf("%f ", t);
	// 交点があるなら
	if (t > 0)
	{
		// 交点 P = s + t * d
        intersection_point.x = camera.coordinates_vec.x + t * dir_vec.x;
        intersection_point.y = camera.coordinates_vec.y + t * dir_vec.y;
        intersection_point.z = camera.coordinates_vec.z + t * dir_vec.z;

		incidence_vec = normalize_vector(subst_vector(light.coordinates_vec, intersection_point));
		normal_dot_incindence = inner_product(plane.orientation_vec, incidence_vec);
		if (normal_dot_incindence < 0.0)
			normal_dot_incindence = 0.0;
		if (normal_dot_incindence > 1.0)
			normal_dot_incindence = 1.0;

		reflection_vec = subst_vector(multi_vector(plane.orientation_vec, 2 * normal_dot_incindence), incidence_vec);
		inverse_camera_orientation_vec = normalize_vector(multi_vector(dir_vec, -1));
		inverse_dot_reflection = inner_product(inverse_camera_orientation_vec, reflection_vec);

		if (inverse_dot_reflection < 0.0)
			inverse_dot_reflection = 0.0;
		if (inverse_dot_reflection > 1.0)
			inverse_dot_reflection = 1.0;

		set_light_ratio(&ambient_coefficientficient, plane.rgb, AMBIENt_coefficientFICIENT);
		set_light_ratio(&ambient_light, ambient_lightning.rgb, ambient_lightning.ratio);

		ambient_light = multi_light_ratio(ambient_light, ambient_coefficientficient);
		set_light_ratio(&diffuse_coefficient, plane.rgb, DIFFUSE_COEFFICIENT);
		set_light_ratio(&diffuse_light, light.rgb, light.ratio * normal_dot_incindence);
		diffuse_light = multi_light_ratio(diffuse_light, diffuse_coefficient);
		set_light_ratio(&specular_coefficient, plane.rgb, SPECULAR_COEFFICIENT);
		set_light_ratio(&specular_light, light.rgb, light.ratio * pow(inverse_dot_reflection, SHININESS));
		specular_light = multi_light_ratio(specular_light, specular_coefficient);
		result_color = add_light_ratio(ambient_light, diffuse_light);
		result_color = add_light_ratio(result_color, specular_light);

		color_value = rgb_to_colorcode(result_color);
		//printf("%d ", color_value);
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

	double	t;

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

	t_plane	plane;
	set(&plane.coordinates_vec, 0, -1, 0);
	set(&plane.orientation_vec, 0, 1, 0);
	plane.rgb.red = 0;
	plane.rgb.green = 246;
	plane.rgb.blue = 246;

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
