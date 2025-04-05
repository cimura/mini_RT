/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:40 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/05 23:21:26 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static bool	is_intersection_in_cylinder_height_range(const t_object *cylinder,
	const t_vector *intersection)
{
	double		i_dot_co;

	i_dot_co = calculate_inner_product(subst_vector(*intersection, cylinder->coordinates_vec),
		cylinder->orientation_vec);
	if (i_dot_co < 0)
		i_dot_co *= -1;
	if (i_dot_co <= cylinder->height / 2)
		return (true);
	else
		return (false);
}

// 交点があれば一番近い交点の情報を登録する
void	set_cylinder_intersection(t_intersection *i, t_object *cylinder,
	const t_ray *ray)
{
	t_coef			coef;
	t_intersection	i1;
	t_intersection	i2;

	calculate_cylinder_intersections_num(&coef, cylinder, ray);
	if (coef.d < 0)
		return ;
	i1.t = ((-1 * coef.b) - sqrt(coef.d)) / (2 * coef.a);
	i2.t = ((-1 * coef.b) + sqrt(coef.d)) / (2 * coef.a);
	if (i1.t > i2.t)
		swap_intersection(&i1, &i2);
	if (i2.t < 0)
		return ;
	i1.coordinates_vec = add_vector(ray->coordinates_vec,
		multi_vector(ray->orientation_vec, i1.t));
	i2.coordinates_vec = add_vector(ray->coordinates_vec,
		multi_vector(ray->orientation_vec, i2.t));
	i1.object = cylinder;
	i2.object = cylinder;
	if (i1.t >= 0
		&& is_intersection_in_cylinder_height_range(cylinder, &i1.coordinates_vec) == true)
		*i = i1;
	else if (i2.t >= 0
		&& is_intersection_in_cylinder_height_range(cylinder, &i2.coordinates_vec) == true)
		*i = i2;
}

// 視線と円柱の表面の法線ベクトルを計算する (円柱データ、交点、円柱の底面の位置ベクトル)
void	set_cylinder_normal_vector(t_intersection *intersection,
	const t_object *cylinder, const t_ray *ray)
{
	t_vector	normal_vector;
	t_vector	cc_to_intersection;
	t_vector	normal_and_co_intersec;
	double		cti_dot_orientation;
	double		ray_dot_noramal;

	cc_to_intersection = subst_vector(intersection->coordinates_vec, cylinder->coordinates_vec);
	cti_dot_orientation = calculate_inner_product(cc_to_intersection, cylinder->orientation_vec);
	normal_and_co_intersec = multi_vector(cylinder->orientation_vec,
		cti_dot_orientation);
	normal_vector = subst_vector(cc_to_intersection, normal_and_co_intersec);
	intersection->hit_on_back = false;
	ray_dot_noramal = calculate_inner_product(ray->orientation_vec, normal_vector);
	if (ray_dot_noramal >= 0)
		normal_vector = multi_vector(normal_vector, -1);
	normal_vector = normalize_vector(normal_vector);
	intersection->normal_vec = normal_vector;
}

