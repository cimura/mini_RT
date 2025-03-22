/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:59:01 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/15 17:16:45 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H

# define MINI_RT_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "vector.h"
# include "ft_mlx.h"
# include "utils.h"
# include "libft.h"

// オブジェクトの識別子
enum	e_obj_identifier
{
	AMBIENT_LIGHTNING = 3,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
};

// RGB 計算しやすく0.0~1.0の範囲で表す
typedef struct	s_color
{
	double	red;
	double	green;
	double	blue;
}	t_dcolor;

// 環境光 Ambient lightning
typedef struct	s_ambient_lightning
{
	int		identifier;
	// 環境光の比率 ambient_lightning_ratio 範囲は[0.0-1.0]
	// 光の強度
	// RGB 範囲は0.0-1.0 ( red,green,blue )
	t_dcolor	intensity;
}	t_ambient_lightning;

// カメラ Camera
typedef struct	s_camera
{
	int			identifier;
	// 座標 ( x,y,z )
	t_vector	coordinates_vec;
	// 3D正規化方向ベクトル 範囲は[-1,1] ( x,y,z )
	t_vector	orientation_vec;// 3d normalized_orientation vector
	// FOV 水平方向の視野角 範囲は[0,180]
	int			horizontal_fov;
	// スクリーン正規化直交基底ベクトル
	t_vector	x_basis;
	t_vector	y_basis;
	// スクリーンの中心点のベクトル
	t_vector	center_of_screen;
}	t_camera;

// 光源 Light
typedef struct	s_light
{
	int			identifier;
	// 座標 ( x,y,z )
	t_vector	coordinates_vec;
	// 光の明るさ比率 範囲は[0.0,1.0]
	// 光の強さ
	// ※mandatoryでは不使用 RGB 範囲は0.0-1.0
	t_dcolor		intensity;
}	t_light;

typedef struct	s_material
{
	// 拡散反射係数
	t_dcolor	diffuse_coef;
	// 鏡面反射係数
	t_dcolor	specular_coef;
	// 光沢度
	double		shinness;
	// 完全鏡面反射を使うかどうか
	bool		use_perfect_reflectance;
	// 完全鏡面反射係数
	t_dcolor	perfect_reflectance;
}	t_material;

// オブジェクト汎用
typedef struct s_object
{
	int			identifier;
	// オブジェクトの位置ベクトル
	t_vector	coordinates_vec;
	// オブジェクトの正規化されている方向ベクトル 範囲は[-1,1]  平面、円柱
	t_vector	orientation_vec;
	// 球体、円柱
	double		diameter;
	// 円柱
	double		height;
	t_material	material;
}	t_object;

// 描画対象の図形（円、平面、円柱）は複数個扱えるように配列にする
typedef struct	s_world
{
	t_mlx				mlx;
	t_ambient_lightning	ambient_lightning;
	t_camera			camera;
	t_light				light;
	t_list				*objects;
}	t_world;

# include "renderer.h"

// *** diaplay.c ***
void	display_in_mlx(t_world world);

// *** parser.c ***
int		parse_arguments(t_world *scene, int argc, char **argv);;

// *** main.c ***
void	on_destroy(t_world world);

#endif
