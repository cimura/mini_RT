#ifndef DRAW_H
# define DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define	WIDTH	512
#define	HEIGHT	512

#define	R	1
/*
	環境光反射係数
		𝑘𝑎=0.01
	拡散反射係数
		𝑘𝑑=0.69
	鏡面反射係数
		𝑘𝑠=0.3
	光沢度
		𝛼=8
	環境光の強度
		𝐼𝑎=0.1
	光源の光の強度
		𝐼𝑖=1.0
*/
typedef struct s_const
{
	const double	k_a;
	const double	k_d;
	const double	k_s;
	const double	I_a;
	const double	I_i;
	const int8_t	alpha;
}	t_const;

#include "vector.h"

typedef struct s_color
{
	double	red;
	double	green;
	double	blue;
	t_const	constant;
}	t_color;

typedef struct s_sphere
{
	t_color	color;
	t_vector	center;
	double	radius;
}	t_sphere;

__int32_t	map(double R_d);

#endif