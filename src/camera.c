/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:26 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/23 17:27:11 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void	set_screen_normalized_basis_vectors(t_camera camera,
	t_vector3 *basisx, t_vector3 *basisy)
{
	t_vector3	up_vec;

	if (fabs(camera.orientation_vec.y) > fabs(camera.orientation_vec.x))
		up_vec = init_vector(0, 0, 1);
	else
		up_vec = init_vector(0, 1, 0);
	*basisx = normalize_vector(cross_product(up_vec, camera.orientation_vec));
	*basisy = cross_product(camera.orientation_vec, *basisx);
}

void	init_camera(t_camera *camera)
{
	set_screen_normalized_basis_vectors(*camera, &camera->x_basis,
		&camera->y_basis);
	camera->center_of_screen = multi_vector(camera->orientation_vec,
			(SCREEN_WIDTH / 2) * (1 / tan(camera->horizontal_fov / 2
					* (M_PI / 180))));
}
