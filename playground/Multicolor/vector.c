#include "draw.h"
#include "vector.h"

t_vector	add_vector(t_vector a, t_vector b)
{
	t_vector	result;
	
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	
	return (result);
}

t_vector	subst_vector(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	
	return (result);
}

t_vector	multi_vector(t_vector v, double c)
{
	t_vector	result;

	result.x = v.x * c;
	result.y = v.y * c;
	result.z = v.z * c;
	return (result);
}

// 二乗
double	abst_squared(t_vector v)
{
	double	result;
	
	result = 0;
	result += v.x * v.x;
	result += v.y * v.y;
	result += v.z * v.z;
	return (result);
}

// 内積
double	inner_product(t_vector a, t_vector b)
{
	double	result;
	
	result = 0;
	result += a.x * b.x;
	result += a.y * b.y;
	result += a.z * b.z;
	return (result);
}

void	set_vector(t_vector *v, double _x, double _y, double _z)
{
	v->x = _x;
	v->y = _y;
	v->z = _z;
}

double	calculate_mirror_reflection(t_const constant, t_vector de, t_vector n, t_vector l)
{
	t_vector	v;
	t_vector	v_tmp;
	t_vector	r;
	t_vector	r_tmp;
	double		inner;
	double		inner2;
	double		R_s;
	
	inner = inner_product(n, l);
	v_tmp = multi_vector(de, -1);
	v = multi_vector(v_tmp, sqrt(1/abst_squared(v_tmp)));
	r_tmp = subst_vector(multi_vector(n, 2*inner), l);
	r = multi_vector(r_tmp, sqrt(1/abst_squared(r_tmp)));
	inner2 = inner_product(v, r);

	R_s = constant.k_s * constant.I_i * pow(inner2, ALPHA);
	if (inner_product(n, l) < 0 || inner_product(v, r) < 0)
		R_s = 0;
	return (R_s);
}
