/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:33 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 16:06:40 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static double	a_coef(const t_vector3 *dir_vec, double co_dot_dir,
	double co_dot_co)
{
	double	dir_dot_dir;

	dir_dot_dir = inner_product(*dir_vec, *dir_vec);
	return (dir_dot_dir - pow(co_dot_dir, 2) / co_dot_co);
}

static double	b_coef(double co_dot_dir, double dir_dot_stc,
	double co_dot_stc, double co_dot_co)
{
	return (2.0 * (dir_dot_stc - co_dot_dir * co_dot_stc / co_dot_co));
}

static double	c_coef(const t_vector3 *camera_to_object,
		const t_object *object,
	double co_dot_stc, double co_dot_co)
{
	double	ctc_dot_ctc;

	ctc_dot_ctc = inner_product(*camera_to_object, *camera_to_object);
	return (ctc_dot_ctc - pow(co_dot_stc, 2)
		/ co_dot_co - pow(object->diameter / 2, 2));
}

void	calculate_cylinder_intersections_num(t_coefficient *coef,
	const t_object *cylinder, const t_ray *ray)
{
	t_vector3	start_to_cylinder;
	double		co_dot_dir;
	double		co_dot_co;
	double		dir_dot_stc;
	double		co_dot_stc;

	start_to_cylinder
		= subst_vector(ray->coordinates_vec, cylinder->coordinates_vec);
	co_dot_dir
		= inner_product(cylinder->orientation_vec,
			ray->orientation_vec);
	co_dot_co
		= inner_product(cylinder->orientation_vec,
			cylinder->orientation_vec);
	dir_dot_stc
		= inner_product(ray->orientation_vec, start_to_cylinder);
	co_dot_stc
		= inner_product(cylinder->orientation_vec, start_to_cylinder);
	coef->a = a_coef(&ray->orientation_vec, co_dot_dir, co_dot_co);
	coef->b = b_coef(co_dot_dir, dir_dot_stc, co_dot_stc, co_dot_co);
	coef->c = c_coef(&start_to_cylinder, cylinder, co_dot_stc, co_dot_co);
	coef->d = pow(coef->b, 2) - 4 * coef->a * coef->c;
}
