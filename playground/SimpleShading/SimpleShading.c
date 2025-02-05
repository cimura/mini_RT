#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "mlx.h"

// 環境光と鏡面反射による陰影処理を追加

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

typedef struct s_imge
{
	void	*ptr;
	char	*pixel_ptr;
	int		bpp;
	int		endian;
	int		line_length;
}				t_imge;

typedef struct s_mlx
{
	void	*ptr;
	void	*win_ptr;
	t_imge	*img;
}	t_mlx;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

void	init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->img = malloc(sizeof(t_imge));
	mlx->win_ptr = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "WINDOW");
	mlx->img->ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (mlx->img->ptr == NULL)
		perror("img");
	mlx->img->pixel_ptr = mlx_get_data_addr(mlx->img->ptr, &mlx->img->bpp, &mlx->img->line_length, &mlx->img->endian);
}

t_vector	subst_vector(t_vector a, t_vector b)
{
	t_vector	result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;

	return (result);
}

t_vector	add_vector(t_vector a, t_vector b)
{
	t_vector	result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return (result);
}

void	init_vector(t_vector *pe, t_vector *pc)
{
	pe->x = 0;
	pe->y = 0;
	pe->z = -5;

	pc->x = 0;
	pc->y = 0;
	pc->z = 5;
}

void	set(t_vector *v, double _x, double _y, double _z)
{
	v->x = _x;
	v->y = _y;
	v->z = _z;
}

double	abst_squared(t_vector v)
{
	double	result;

	result = 0;
	result += v.x * v.x;
	result += v.y * v.y;
	result += v.z * v.z;

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

double	inner_product(t_vector a, t_vector b)
{
	double	result;

	result = 0;
	result += a.x * b.x;
	result += a.y * b.y;
	result += a.z * b.z;

	return (result);
}

void	my_pixel_put(int x, int y, t_imge *img, int color)
{
	// printf("img ptr: %p\n", img);
	// printf("pixel ptr: %p\n", img->pixel_ptr);
	// printf("pixel value: %d\n", *img->pixel_ptr);
	int	offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = (y * img->line_length) + (x * (img->bpp / 8));
		*(unsigned int *)(img->pixel_ptr + offset) = color;
	}
}

int32_t	map(double R_d)
{
	int32_t	result;
	int	red;
	int green;
	int	blue;

	red = 255 * R_d;
	green = 255 * R_d;
	blue = 255 * R_d;

	result = red * pow(16, 4) + green * pow(16, 2) + blue;
	return (result);
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

	R_s = constant.k_s * constant.I_i * pow(inner2, constant.alpha);
	if (inner_product(n, l) < 0 || inner_product(v, r) < 0)
		R_s = 0;
	return (R_s);
}

/*	de:	perspective vector 
	pe: perspective position 
	pc:	center of sphere 
	pw: screen position
	d_light: light vector
	n: normal vector
	p_i: 視線と球の交点
	p_l: 点光源の位置
	𝑅𝑎：環境光の反射光の放射輝度
	𝑅𝑑：直接光の拡散反射光の放射輝度
	𝑅𝑠：直接光の鏡面反射光の放射輝度
*/

/*
	𝑅𝑠=𝑘𝑠𝐼𝑖(𝐯⃗ ⋅𝐫⃗ )𝛼
	𝑘𝑠：鏡面反射係数
	𝐼𝑖：光源の光の強度
	𝐯⃗ ：視線ベクトルの逆ベクトル(∣∣𝐯⃗ ∣∣=1)
	𝐫⃗ ：入射光の正反射ベクトル(∣∣𝐫⃗ ∣∣=1)
	𝛼：光沢度(1≤𝛼)
*/
int	main() {
	t_const constant = {
	.k_a = 0.01,
	.k_d = 0.69,
	.k_s = 0.3,
	.I_a = 0.1,
	.I_i = 1.0,
	.alpha = 8
};
	t_mlx	mlx;
	init(&mlx);
	t_vector	de;
	t_vector	pe;
	t_vector	pc;
	t_vector	pw;
	t_vector	v_tmp;
	t_vector	d_light;
	t_vector	n;
	t_vector	l;
	t_vector	p_i;

	double	xs, ys;
	double	xw, yw;

	double	R_r;
	double	R_a;
	double	R_d;
	double	R_s;
	double	answer1, answer2;
	double	t;

	ys = 0;
	init_vector(&pe, &pc);
	d_light.x = 5;
	d_light.y = 5;
	d_light.z = -5;
	R_a = constant.k_a * constant.I_a;
	while (ys < HEIGHT)
	{
		xs = 0;
		yw = (-2 * ys) / (HEIGHT - 1) + 1.0;
		while (xs < WIDTH)
		{
			// printf("xs-> %f, ys-> %f\n", xs, ys);
			xw = (2 * xs) / (WIDTH - 1) - 1.0;
			set(&pw, xw, yw, 0);
			de = subst_vector(pw, pe);
			v_tmp = subst_vector(pe, pc);

			double	A = abst_squared(de);
			double	B = 2 * inner_product(de, v_tmp);
			double	C = abst_squared(v_tmp) - R*R;

			double	D = B*B - 4*A*C;
			if (D == 0)
			{
				t = -B/(2*A);
			}
			else if (D > 0)
			{
				answer1 = (-B - sqrt(D))/ (2*A);
				answer2 = (-B + sqrt(D))/ (2*A);
				if (answer1 > 0)
					t = answer1;
				else
					t = answer2;

				// printf("Answer: %f\n", answer1);

				p_i = add_vector(pe, multi_vector(de, t));

				t_vector	n_tmp;
				n_tmp = subst_vector(p_i, pc);
				n = multi_vector(n_tmp, 1 / sqrt(abst_squared(n_tmp)));

				t_vector	l_tmp;
				l_tmp = subst_vector(d_light, p_i);
				l = multi_vector(l_tmp, 1 / sqrt(abst_squared(l_tmp)));

				R_d = constant.k_d * constant.I_i * inner_product(n, l);
				if (D == 0 || inner_product(n, l) < 0)
					R_d = 0;
				R_s = calculate_mirror_reflection(constant, de, n, l);

				R_r = R_a + R_d + R_s;
				// R_r = R_a + R_s;
				my_pixel_put(xs, ys, mlx.img, map(R_r));
			}
			else
				my_pixel_put(xs, ys, mlx.img, 0xA0A0FF);
			xs++;
		}
		ys++;
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->ptr, 0, 0);
	mlx_loop(mlx.ptr);
}
