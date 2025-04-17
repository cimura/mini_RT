/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:34 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/17 19:08:50 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H

# define VECTOR_H

# include <math.h>

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

// *** vector.c ***
t_vector3	subst_vector(t_vector3 a, t_vector3 b);
t_vector3	add_vector(t_vector3 a, t_vector3 b);
t_vector3	multi_vector(t_vector3 v, double c);
double		len_vector(t_vector3 v);
t_vector3	normalize_vector(t_vector3 v);

// *** vector_utils.c ***
double		abst_squared(t_vector3 v);
double		inner_product(t_vector3 a, t_vector3 b);
t_vector3	cross_product(t_vector3 a, t_vector3 b);

#endif