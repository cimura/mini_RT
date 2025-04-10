/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:40 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/10 17:48:43 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H

# define RENDERER_H

# include "mini_rt.h"
# include "vector.h"

// 完全鏡面反射をするときの再帰関数の深さ限度
# define MAX_RECURSIVE_LEVEL 6

// 仮想スクリーンの大きさ (ワールド座標内)
# define SCREEN_WIDTH 2.0
# define SCREEN_HEIGHT 2.0

// 背景色
# define BACKGROUND_COLOR_RED 0.7
# define BACKGROUND_COLOR_GREEN 0.7
# define BACKGROUND_COLOR_BLUE 0.7

// 2次元の座標を表す構造体
typedef struct s_xy
{
	double	x;
	double	y;
}	t_xy;

// レイ（視線）用の構造体
typedef struct s_ray
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
typedef struct s_intersection
{
	// 係数t
	double		t;
	bool		hit_on_back;
	t_vector	coordinates_vec;
	t_vector	normal_vec;
	t_object	*object;
}	t_intersection;

// *** anti_aliasing.c ***
int				anti_aliasing(t_world *world);

// *** camera.c ***
void			init_camera(t_camera *camera);

// *** sphere.c ***
void			set_sphere_intersection(t_intersection *i, t_object *sphere,
					const t_ray *ray);
void			set_sphere_normal_vector(t_intersection *intersection,
					const t_object *sphere, const t_ray *ray);
t_xy			get_uv_on_sphere(const t_vector *intersection_vec,
					const t_object *sphere);

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
void			calculate_cylinder_intersections_num(t_coef *coef,
					const t_object *cylinder, const t_ray *ray);

/// *** intersections.c ***
void			swap_intersection(t_intersection *i1, t_intersection *i2);
t_intersection	find_intersection_minimum_distance(t_world world,
					const t_ray *ray);
void			calculate_intersections_normal_vector(t_intersection *i,
					const t_ray *ray);

// *** texture_mapping.c ***
void			set_bumpmap_normal_vector(t_intersection *i, t_texture *normal_tex,
					const t_object *object);

// *** renderer.c ***
t_dcolor		ray_trace_recursive(const t_world *world, const t_ray *ray,
					int recursion_level);

#endif