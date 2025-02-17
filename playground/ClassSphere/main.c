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

double	calculate_intersection(t_vector pe, t_vector pc, t_vector de)
{
	t_vector v_tmp = subst_vector(pe, pc);
	double A = abst_squared(de);
	double B = 2 * inner_product(de, v_tmp);
	double C = abst_squared(v_tmp) - R * R;
	double D = B * B - 4 * A * C;

	double	t;

	if (D == 0)
		t = -B / (2 * A);
	else if (D > 0)
	{
		double answer1 = (-B - sqrt(D)) / (2 * A);
		double answer2 = (-B + sqrt(D)) / (2 * A);
		if (answer1 > 0)
			t = answer1;
		else
			t = answer2;
	}
	else
		t = -1;
	return (t);
}

t_vector calculate_normal(t_vector p_i, t_vector pc)
{
	t_vector n_tmp = subst_vector(p_i, pc);
	return multi_vector(n_tmp, 1 / sqrt(abst_squared(n_tmp)));
}

double calculate_lighting(t_color color, t_vector de, t_vector n, t_vector l)
{
	double R_a = color.constant.k_a * color.constant.I_a;
	double R_d = color.constant.k_d * color.constant.I_i * inner_product(n, l);
	if (inner_product(n, l) < 0)
		R_d = 0;
	double R_s = calculate_mirror_reflection(color.constant, de, n, l);

	return R_a + R_d + R_s;
}

void render_pixel(int xs, int ys, t_vector pe, t_vector pc, t_vector d_light, t_vector pw, t_color red, t_color green, t_color blue, t_mlx mlx)
{
	t_vector de, p_i, n, l;
	double t;

	de = subst_vector(pw, pe);

	t = calculate_intersection(pe, pc, de);
	if (t > 0)
	{
		p_i = add_vector(pe, multi_vector(de, t));
		n = calculate_normal(p_i, pc);
		t_vector l_tmp = subst_vector(d_light, p_i);
		l = multi_vector(l_tmp, 1 / sqrt(abst_squared(l_tmp)));

		red.R_r = calculate_lighting(red, de, n, l);
		green.R_r = calculate_lighting(green, de, n, l);
		blue.R_r = calculate_lighting(blue, de, n, l);
		// if (xs >= WIDTH/2 -10 && xs <= WIDTH/2 + 10
		// 	&& ys >= HEIGHT/2 -10 && ys <= HEIGHT/2 + 10)
		// {
		// 	printf("RED: %f\n", red.R_r);
		// 	printf("GREEN: %f\n", green.R_r);
		// 	printf("BLUE: %f\n", blue.R_r);
		// }

		my_pixel_put(xs, ys, mlx.img, map(red, green, blue));
	}
	else
		my_pixel_put(xs, ys, mlx.img, 0x303030);
}

void render_scene(t_mlx mlx, t_color red, t_color green, t_color blue, t_vector pe, t_vector pc, t_vector d_light)
{
	t_vector	pw;
	double xs, ys;
	double xw, yw;
	for (ys = 0; ys < HEIGHT; ys++)
	{
		yw = (-2 * ys) / (HEIGHT - 1) + 1.0;
		for (xs = 0; xs < WIDTH; xs++)
		{
			xw = (2 * xs) / (WIDTH - 1) - 1.0;
			set(&pw, xw, yw, 0);
			render_pixel(xs, ys, pe, pc, d_light, pw, red, green, blue, mlx);
		}
	}
}

void	init_color(t_color *color, double value, double k_a, double k_d, double k_s, double I_a, double I_i)
{
	color->value = value;
	color->constant.k_a = k_a;
	color->constant.k_d = k_d;
	color->constant.k_s = k_s;
	color->constant.I_a = I_a;
	color->constant.I_i = I_i;
}

int	main() {
	t_mlx	mlx;
	init(&mlx);

	t_color	red, green, blue;
	init_color(&red, 255, 0.01, 0.69, 0.30, 0.10, 1.00);
	init_color(&green, 255, 0, 0.2, 0.30, 0.10, 1.00);
	init_color(&blue, 255, 0.01, 0, 0.30, 0.10, 1.00);

	t_vector	pe, pc;
	t_vector	d_light;
	init_vector(&pe, &pc);
	d_light.x = 5;
	d_light.y = 5;
	d_light.z = -5;
	render_scene(mlx, red, green, blue, pe, pc, d_light);
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->ptr, 0, 0);
	mlx_loop(mlx.ptr);
}
