#include "draw.h"
#include "ft_mlx.h"
#include "vector.h"

/*	de:	視線ベクトル
	pe: 視線位置
	pc:	球の中心
	pw: スクリーンの位置
	d_light: 光源ベクトル
	n: ノーマルベクトル
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
