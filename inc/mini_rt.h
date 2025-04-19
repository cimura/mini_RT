/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:59:01 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/19 16:34:34 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H

# define MINI_RT_H

# define DEBUG

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "vector.h"
# include "dcolor.h"
# include "texture.h"
# include "ft_mlx.h"
# include "utils.h"
# include "libft.h"

// オブジェクトの識別子
enum	e_obj_identifier
{
	ATOMOSPHERE = 3,
	AMBIENT_LIGHTNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
};

// 環境光 Ambient lightning
typedef struct s_ambient_lightning
{
	int			identifier;
	// 環境光の比率 ambient_lightning_ratio 範囲は[0.0-1.0]
	// 光の強度
	// RGB 範囲は0.0-1.0 ( red,green,blue )
	t_dcolor	intensity;
}	t_ambient_lightning;

// カメラ Camera
typedef struct s_camera
{
	int			identifier;
	// 座標 ( x,y,z )
	t_vector3	coordinates_vec;
	// 3D正規化方向ベクトル 範囲は[-1,1] ( x,y,z )
	t_vector3	orientation_vec;// 3d normalized_orientation vector
	// FOV 水平方向の視野角 範囲は[0,180]
	int			horizontal_fov;
	// スクリーン正規化直交基底ベクトル
	t_vector3	x_basis;
	t_vector3	y_basis;
	// スクリーンの中心点のベクトル
	t_vector3	center_of_screen;
}	t_camera;

// 光源 Light
typedef struct s_light
{
	int			identifier;
	// 座標 ( x,y,z )
	t_vector3	coordinates_vec;
	// 光の明るさ比率 範囲は[0.0,1.0]
	// 光の強さ
	// ※mandatoryでは不使用 RGB 範囲は0.0-1.0
	t_dcolor	intensity;
}	t_light;

// 完全鏡面反射する鏡は銀で出来ていることにする
//# define GLASS "GLASS"
//# define IRON "IRON"
//# define SILVER "SILVER"
//# define WOOD "WOOD"
//# define WATER "WATER"
enum	e_material
{
	GLASS,
	IRON,
	SILVER,
	WOOD,
	WATER,
};

typedef struct s_material
{
	// 拡散反射係数
	t_dcolor	diffuse;
	// 鏡面反射係数
	t_dcolor	specular;
	// 光沢度
	double		shinness;
	// 完全鏡面反射を使うかどうか
	bool		use_perfect_reflectance;
	// 完全鏡面反射・屈折係数
	t_dcolor	catadioptric_factor;
	// 屈折を使うかどうか
	bool		use_refraction;
	// 絶対屈折率
	double		refractive_index;
	// 面が表と裏を共有するかどうか（円柱や平面などはtrue 球体はfalse）
	bool		use_thin_surfase;
}	t_material;

// オブジェクト汎用
typedef struct s_object
{
	int				identifier;
	// オブジェクトの位置ベクトル
	t_vector3		coordinates_vec;
	// オブジェクトの正規化されている方向ベクトル 範囲は[-1,1]  平面、円柱
	t_vector3		orientation_vec;
	// 球体、円柱
	double			diameter;
	// 円柱
	double			height;
	t_list			*textures;
	t_material		material;
}	t_object;

// 描画対象の図形（円、平面、円柱）は複数個扱えるように配列にする
typedef struct s_world
{
	t_mlx				mlx;
	t_dcolor			**frame_buffer;
	// シーン全体のオブジェクトの情報 （大気など）
	t_texture			*skybox;
	double				global_refractive_index;
	t_ambient_lightning	ambient_lightning;
	t_camera			camera;
	t_list				*lights;
	t_list				*objects;
}	t_world;

//# include "renderer.h"

// *** diaplay.c ***
void		display_in_mlx(t_world *world);

// *** parser.c ***
int			parse_arguments(t_world *scene, int argc, char **argv);

// *** renderer.c ***
int			renderer(t_world *world);

t_dcolor	**frame_buffer_init(int width, int height);

// *** main.c ***
void		world_destroy(t_world *world);
void		on_destroy(t_world *world);

#endif
