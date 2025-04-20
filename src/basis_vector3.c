/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis_vector3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:01:47 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:38:51 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_basis_vectors	get_basis_vectors_from_normal_vec(const t_vector3 *normal_vec)
{
	t_basis_vectors	basis_vec;
	t_vector3		arbitrary;

	arbitrary = init_vector(0, 1, 0);
	if (fabs(normal_vec->x) > 0.9)
		arbitrary = init_vector(1, 0, 0);
	basis_vec.u = normalize_vector(cross_product(arbitrary, *normal_vec));
	basis_vec.v = normalize_vector(cross_product(*normal_vec, basis_vec.u));
	return (basis_vec);
}
