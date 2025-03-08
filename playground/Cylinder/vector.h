#ifndef VECTOR_H
# define VECTOR_H

#include "draw.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector	subst_vector(t_vector a, t_vector b);
t_vector	add_vector(t_vector a, t_vector b);

// 複数オブジェクトの生成のため、何かしらの工夫が必要
void		init_vector1(t_vector *pe1, t_vector *pc1);
void		init_vector2(t_vector *pe2, t_vector *pc2);
void		init_vector3(t_vector *pe3, t_vector *pc3);


void		set(t_vector *v, double _x, double _y, double _z);
double		abst_squared(t_vector v);
t_vector	multi_vector(t_vector v, double c);
double		dot_vector(t_vector a, t_vector b);
t_vector	normalize_vector(t_vector v);
double		inner_product(t_vector a, t_vector b);
double		calculate_mirror_reflection(t_const constant, t_vector de, t_vector n, t_vector l);

#endif