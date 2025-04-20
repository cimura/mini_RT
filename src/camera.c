/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:26 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:38:58 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void	set_screen_normalized_basis_vectors(t_camera camera,
	t_vector3 *basisx, t_vector3 *basisy)
{
	basisx->y = 0;
	basisx->x = camera.orientation_vec.z
		/ sqrt(pow(camera.orientation_vec.z, 2)
			+ pow(camera.orientation_vec.x, 2));
	basisx->z = -1 * camera.orientation_vec.x
		/ sqrt(pow(camera.orientation_vec.x, 2)
			+ pow(camera.orientation_vec.z, 2));
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
