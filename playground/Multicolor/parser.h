/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:16:38 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/17 14:48:17 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
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
	INV_NUMBER,
	OUT_OF_RANGE,
	INV_PARAM,
	NOT_MATCH_PARAM_NUM,
};

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

// *** parser.c ***
void	print_err_msg(int errnum, char *arg);
int		parse_arguments(t_scene_data *scene, int argc, char **argv);
void	free_double_pointer(char **pointer);

// *** parse_objects.c ***
int		parse_ambient_lightning(t_scene_data *scene, char **per_word_pointer);
int		parse_camera(t_scene_data *scene, char **per_word_pointer);
int		parse_light(t_scene_data *scene, char **per_word_pointer);

// *** libft2.c *** utils.hなどに移してもいいかも
double	ft_atod(char *nptr);
int     ft_strrncmp(const char *s1, const char *s2, size_t size);
int		ft_double_pointer_size(char **pointers);

// *** libft3.c *** utils.hなどに移してもいいかも
int		ft_char_count(char *src, char target);

#endif