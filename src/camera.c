/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:26 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/08 17:21:15 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

// 今回はカメラの回転は指定されないので、x軸に水平でy軸に平行な角度
static void	set_screen_normalized_basis_vectors(t_camera camera,
	t_vector *basisx, t_vector *basisy)
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
