#include "minirt.h"

typedef struct	s_light_ratio
{
	double	red;
	double	green;
	double	blue;
}	t_light_ratio;

typedef struct	s_light_info
{
		// 物体の表面の色によって変える
	t_light_ratio		ambient_coefficient;
	t_light_ratio		diffuse_coefficient;
	t_light_ratio		specular_coefficient;

		// 光の色によって変える
	t_light_ratio		ambient_light;
	t_light_ratio		diffuse_light;
	t_light_ratio		specular_light;
	t_light_ratio		result_color;
}	t_light_info;

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

void	set_light_ratio(t_light_ratio *light, t_rgb rgb, double coefficient);
t_light_ratio	add_light_ratio(t_light_ratio l1, t_light_ratio l2);
t_light_ratio	multi_light_ratio(t_light_ratio l1, t_light_ratio l2);
int	rgb_to_colorcode(t_light_ratio light);
int	calculate_color(t_light light, t_object *objects, t_vector dir_vec, t_ambient_lightning ambient_lightning, t_vector intersection_point);