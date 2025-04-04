/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:40 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/05 23:32:17 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H

# define RENDERER_H

# include "mini_rt.h"
# include "vector.h"


// 諸々の定数を定義しておく
// 環境光反射係数
//# define AMBIENT_COEFFICIENT 0.2
// 拡散反射光反射係数
//# define DIFFUSE_COEFFICIENT 0.69
// 鏡面反射係数
# define SPECULAR_COEFFICIENT 0.0//0.8
// 光沢度
# define SHININESS 8
// 完全鏡面反射をするときの再帰関数の深さ限度
# define MAX_RECURSIVE_LEVEL 6
// shadow rayを計算するための微小値
# define EPSILON 1.0 / 512

// 仮想スクリーンの大きさ
# define SCREEN_WIDTH 2.0
# define SCREEN_HEIGHT 2.0

// 背景色
# define BACKGROUND_COLOR_RED 0.12
# define BACKGROUND_COLOR_GREEN 0.56
# define BACKGROUND_COLOR_BLUE 1.0

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
	double		prev_refractive_index;
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
	bool		hit_on_back;
	t_vector	coordinates_vec;
	t_vector	normal_vec;
	t_object	*object;
}	t_intersection;

// 完全鏡面反射と屈折を計算するための構造体
typedef struct	s_catadioptric_vars
{
	t_vector	inverse_ray_vec;
	double		inverse_ray_dot_normal;
	double		refraction_index1;
	double		refraction_index2;
	double		rfl_2_1;
	double		cos1;
	double		cos2;
	double		omega;
	double		p_polarized_light;
	double		s_polarized_light;
	double		reflectance_index;
}	t_catadioptric_vars;

// *** calculate_phong_radiance.c ***
t_dcolor		calculate_phong_radiance(const t_world *world, const t_intersection *i,
	const t_ray *ray);

// *** catadioptric.c ***
t_dcolor		calculate_catadioptric_radiance(const t_world *world,
	t_intersection *intersection, const t_ray *ray, int recursion_level);

// *** canera.c ***
void			init_camera(t_camera *camera);

// *** sphere.c ***
void			set_sphere_intersection(t_intersection *i, t_object *sphere,
	const t_ray *ray);
void			set_sphere_normal_vector(t_intersection *intersection,
	const t_object *sphere, const t_ray *ray);

// *** plane.c ***
void			set_plane_intersection(t_intersection *i, t_object *plane,
	const t_ray *ray);
void			set_plane_normal_vector(t_intersection *intersection,
	const t_object *plane, const t_ray *ray);

// *** cylinder.c ***
void			set_cylinder_intersection(t_intersection *i, t_object *cylinder,
	const t_ray *ray);
void			set_cylinder_normal_vector(t_intersection *intersection,
	const t_object *cylinder, const t_ray *ray);

// *** cylinder_utils.c ***
void			calculate_cylinder_intersections_num(t_coef *coef, const t_object *cylinder,
	const t_ray *ray);

/// *** intersections.c ***
void			swap_intersection(t_intersection *i1, t_intersection *i2);
t_intersection	find_intersection_minimum_distance(t_world world,
	const t_ray *ray);
void	calculate_intersections_normal_vector(t_intersection *i,
	const t_ray *ray);

// *** dcolor.c ***
t_dcolor		dcolor_coef_multi(t_dcolor rgb, double coefficient);
t_dcolor		dcolor_init(double red, double green, double blue);
t_dcolor		dcolor_add(t_dcolor l1, t_dcolor l2);
t_dcolor		dcolor_multi(t_dcolor l1, t_dcolor l2);
int				rgb_to_colorcode(t_dcolor light);

// *** renderer.c ***
t_dcolor		ray_trace_recursive(const t_world *world, const t_ray *ray,
	int recursion_level);
int 			render_scene(t_world *world);

#endif