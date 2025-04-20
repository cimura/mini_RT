/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:34 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/19 14:12:18 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H

# define VECTOR_H

# include <math.h>

// 2次元の座標を表す構造体
typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_basis_vector
{
	t_vector3	u;
	t_vector3	v;
}	t_basis_vector;

// *** vector.c ***
t_vector3	subst_vector(t_vector3 a, t_vector3 b);
t_vector3	add_vector(t_vector3 a, t_vector3 b);
t_vector3	multi_vector(t_vector3 v, double c);
double		len_vector(t_vector3 v);
t_vector3	normalize_vector(t_vector3 v);

// *** vector_utils.c ***
t_vector3		init_vector(double x, double y, double z);
double			abst_squared(t_vector3 v);
double			inner_product(t_vector3 a, t_vector3 b);
t_vector3		cross_product(t_vector3 a, t_vector3 b);
t_basis_vector	get_basis_vector_from_normal_vec(const t_vector3 *normal_vec);

#endif