/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:16:38 by ttakino           #+#    #+#             */
/*   Updated: 2025/02/25 14:53:26 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "vector.h"
# include "libft.h"

enum	e_errnum
{
	INV_NUM_OF_ARGS,
	INV_FILENAME,
	FILE_TOO_LARGE,
	FILE_NOT_FOUND,
	CANT_READ_FILE,
	INV_IDENTIFIER,
};

// 環境光 Ambient lightning
typedef struct	s_ambient_lightning
{
	char			*identifier;
	// 環境光の比率 ambient_lightning_ratio
	double			ambient_lightning_ratio;
	// RGB 範囲は0-255 ( red,green,blue )
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_ambient_lightning;

// カメラ Camera
typedef struct	s_camera
{
	char		identifier;
	// 座標 ( x,y,z )
	double		x;
	double		y;
	double		z;
	// 3D正規化方向ベクトル 範囲は[-1,1] ( x,y,z )
	t_vector	nov_3d;// 3d normalized_orientation vector
	// FOV 水平方向の視野角 範囲は[0,180]
	int			horizontal_fov;
}	t_camera;

// 光源 Light
typedef struct	s_light
{
	char			identifier;
	// 座標 ( x,y,z )
	double			x;
	double			y;
	double			z;
	// 光の明るさ比率 範囲は[0.0,1.0]
	double			light_brightness_ratio;
	// ※mandatoryでは不使用 RGB 範囲は0-255
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_light;

// 球 Sphere
typedef struct	s_sphere
{
	char			*identifier;
	// 座標 ( x,y,z )
	double			x;
	double			y;
	double			z;
	// 直径
	double			diameter;
	// RGB 範囲は0-255
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_sphere;

// 平面 Plane
typedef struct	s_plane
{
	char			*identifier;
	// 座標 (x,y,z)
	double			x;
	double			y;
	double			z;
	// 3D正規化法線ベクトル 範囲は[-1,1] (x,y,z)
	t_vector		nov_3d;// 3d normalized orientation vector
	// RGB 範囲は0-255
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_plane;

// 円柱 Cylinder
typedef struct	s_cylinder
{
	char			*identifier;
	// 座標 (x,y,z)
	double			x;
	double			y;
	double			z;
	// 円柱の軸の三次元正規化ベクトル 範囲は[-1,1] (x,y,z)
	t_vector		nv_ac_3d;//  3d normalized vector of axis of cylinder
	// 直径
	double			diameter;
	// 高さ
	double			height;
	// RGB 範囲は0-255
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_cylinder;

// 描画対象の図形（円、平面、円柱）は複数個扱えるように配列にする
typedef struct	s_scene_data
{
	t_ambient_lightning	ambient_lightning;
	t_camera			camera;
	t_light				light;
	t_sphere			*spheres;
	t_plane				*planes;
	t_cylinder			*cylinders;
}	t_scene_data;

int	parse_arguments(int argc, char **argv);

#endif