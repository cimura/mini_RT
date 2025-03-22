#include "mini_rt.h"

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

//double	calculate_intersection(t_vector pe, t_vector pc, t_vector de)
//{
//	t_vector v_tmp = subst_vector(pe, pc);
//	double A = abst_squared(de);
//	double B = 2 * inner_product(de, v_tmp);
//	double C = abst_squared(v_tmp) - R * R;
//	double D = B * B - 4 * A * C;

//	double	t;

//	if (D == 0)
//		t = -B / (2 * A);
//	else if (D > 0)
//	{
//		double answer1 = (-B - sqrt(D)) / (2 * A);
//		double answer2 = (-B + sqrt(D)) / (2 * A);
//		if (answer1 > 0)
//			t = answer1;
//		else
//			t = answer2;
//	}
//	else
//		t = -1;
//	return (t);
//}

//t_vector calculate_normal(t_vector p_i, t_vector pc)
//{
//	t_vector n_tmp = subst_vector(p_i, pc);
//	return multi_vector(n_tmp, 1 / sqrt(abst_squared(n_tmp)));
//}

//double calculate_lighting(t_dcolor color, t_vector de, t_vector n, t_vector l)
//{
//	double R_a = color.constant.k_a * color.constant.I_a;
//	double R_d = color.constant.k_d * color.constant.I_i * inner_product(n, l);
//	if (inner_product(n, l) < 0)
//		R_d = 0;
//	double R_s = calculate_mirror_reflection(color.constant, de, n, l);

//	return R_a + R_d + R_s;
//}

// void render_pixel(int xs, int ys, t_object object, t_vector d_light, t_vector pw, t_mlx mlx)
// {
// 	t_vector pe, de, p_i, n, l, best_pc;
// 	set(&pe, 0, 0, -5);

// 	de = subst_vector(pw, pe);

// 	if (min_t != INFINITY)
// 	{
// 		// printf("min_t: %f\n", min_t);
// 		p_i = add_vector(pe, multi_vector(de, min_t));
// 		n = calculate_normal(p_i, best_pc);
// 		t_vector l_tmp = subst_vector(d_light, p_i);
// 		l = multi_vector(l_tmp, 1 / sqrt(abst_squared(l_tmp)));

// 		red.R_r = calculate_lighting(red, de, n, l);
// 		green.R_r = calculate_lighting(green, de, n, l);
// 		blue.R_r = calculate_lighting(blue, de, n, l);

// 		my_pixel_put(xs, ys, mlx.img, map(red, green, blue));
// 	}
// 	else
// 		my_pixel_put(xs, ys, mlx.img, 0x303030);
// }

// プログラムを終了するときに呼ぶ mlx関係のポインタをfreeする mlx以外をfreeするようにしてもいいかも
void	on_destroy(t_world world)
{
	if (world.mlx.img && world.mlx.img->ptr)
		mlx_destroy_image(world.mlx.ptr, world.mlx.img->ptr);
	if (world.mlx.win_ptr)
		mlx_destroy_window(world.mlx.ptr, world.mlx.win_ptr);
	if (world.mlx.ptr)
	{
		mlx_destroy_display(world.mlx.ptr);
		free(world.mlx.ptr);
	}
	ft_lstclear(&world.objects, NULL);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_world	world;

	if (parse_arguments(&world, argc, argv) != 0)
		return (1);
	if (init_mlx_struct(&world.mlx) != 0)
		return (1);
	render_scene(world);
	display_in_mlx(world);
}
