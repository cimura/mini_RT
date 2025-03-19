#ifndef RENDERER_H

# define RENDERER_H

# include "mini_rt.h"
# include "vector.h"


// 諸々の定数を定義しておく あとで全体の構造体に入れる
// 環境光反射係数
# define	AMBIENT_COEFFICIENT 0.2
// 拡散反射光反射係数
# define	DIFFUSE_COEFFICIENT 0.69
// 鏡面反射係数
# define SPECULAR_COEFFICIENT 0.8
// 光沢度
# define SHININESS 8
// shadow rayを計算するための微小値
# define EPSILON 0.002

// 仮想スクリーンの大きさ
# define SCREEN_WIDTH 2.0
# define SCREEN_HEIGHT 2.0

// 背景色
# define BACKGROUND_COLOR 0xaaaaaa


typedef struct	s_light_ratio
{
	double	red;
	double	green;
	double	blue;
}	t_light_ratio;

// 2次元の座標を表す構造体
typedef struct	s_xy
{
	double	x;
	double	y;
}	t_xy;

// レイ（視線）用の構造体
typedef struct	s_ray
{
	t_vector	coordinates_vec;
	t_vector	orientation_vec;
}	t_ray;

// P = S + td tの二次方程式の係数a,b,c 判別式d  (S: レイの始点 t: 実数(0<t) d: レイの正規化方向ベクトル)
typedef struct s_coef
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_coef;

// レイと一番近い物体の交点の情報
typedef struct	s_intersection
{
	// 係数t
	double		t;
	t_vector	coordinates_vec;
	t_vector	normal_vec;
	t_object	object;
}	t_intersection;

// *** calculate_pixel_color.c ***
int				calculate_pixel_color(t_world world, t_intersection i, t_ray ray);

// *** canera.c ***
void			init_camera(t_camera *camera);

// *** cylinder_utils.c ***
void			calculate_cylinder_intersections_num(t_coef *coef, t_object cylinder, t_ray ray);

// *** cylinder.c ***
void			get_cylinder_intersection(t_intersection *i, t_ray ray, t_object object);
t_vector		calculate_cylinder_normal_vector(t_object cylinder, t_vector intersection, t_ray ray);

/// *** intersections.c ***
void			swap_intersection(t_intersection *i1, t_intersection *i2);
t_intersection	find_intersection_minimum_distance(t_world world, t_ray ray);
void			calculate_intersections_normal_vector(t_intersection *i, t_ray ray);

// *** light_ratio.c ***
void			set_light_ratio(t_light_ratio *light, t_rgb rgb, double coefficient);
t_light_ratio	add_light_ratio(t_light_ratio l1, t_light_ratio l2);
t_light_ratio	multi_light_ratio(t_light_ratio l1, t_light_ratio l2);
int				rgb_to_colorcode(t_light_ratio light);

// *** renderer.c ***
void 			render_scene(t_world world);

#endif