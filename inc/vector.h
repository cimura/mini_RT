/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:34 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/08 00:09:09 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H

# define VECTOR_H

# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

// *** vector.c ***
t_vector	subst_vector(t_vector a, t_vector b);
t_vector	add_vector(t_vector a, t_vector b);
t_vector	multi_vector(t_vector v, double c);
double		len_vector(t_vector v);
t_vector	normalize_vector(t_vector v);

// *** vector_utils.c ***
double		abst_squared(t_vector v);
double		inner_product(t_vector a, t_vector b);
t_vector	cross_product(t_vector a, t_vector b);

#endif