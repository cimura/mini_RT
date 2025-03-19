/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:59:01 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/17 15:21:51 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H

# define MINI_RT_H

# define AMBIENT_LIGHTNING "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLANE "pl"
# define CYLINDER "cy"


# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "vector.h"
# include "ft_mlx.h"
# include "libft/inc/libft.h"

// RGB 計算しやすく0.0~1.0の範囲で表す
typedef struct	s_rgb
{
	double	red;
	double	green;
	double	blue;
}	t_rgb;


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

// 球 Sphere
typedef struct	s_sphere
{
	char		*identifier;
	// 座標 ( x,y,z )
	t_vector	coordinates_vec;
	// 直径
	double		diameter;
	// RGB 範囲は0.0-1.0
	t_rgb		rgb;
}	t_sphere;

// 平面 Plane
typedef struct	s_plane
{
	char		*identifier;
	// 座標 (x,y,z)
	t_vector	coordinates_vec;
	// 3D正規化法線ベクトル 範囲は[-1,1] (x,y,z)
	t_vector	orientation_vec;// 3d normalized orientation vector
	// RGB 範囲は0.0-1.0
	t_rgb		rgb;
}	t_plane;

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

// オブジェクト汎用
typedef struct s_object
{
	char		*identifier;
	// オブジェクトの位置ベクトル
	t_vector	coordinates_vec;
	// オブジェクトの正規化されている方向ベクトル 範囲は[-1,1]  平面、円柱
	t_vector	orientation_vec;
	// 球体、円柱
	double		diameter;
	// 円柱
	double		height;
	// RGB 範囲は0.0-1.0
	t_rgb		rgb;
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

#endif