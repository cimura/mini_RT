/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:13:53 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:28:04 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H

# define SHADER_H

# include "mini_rt.h"
# include "renderer.h"

# define EPSILON 0.005

typedef struct s_catadioptric_vars
{
	t_vector3	inverse_ray_vec;
	double		inverse_ray_dot_normal;
	double		refraction_index1;
	double		refraction_index2;
	double		cos1;
	double		cos2;
	double		omega;
	double		p_polarized_light;
	double		s_polarized_light;
	double		reflectance_index;
}	t_catadioptric_vars;

// *** shader.c ***
t_dcolor		shader(const t_world *world, const t_intersection *i,
					const t_ray *ray);

// *** catadioptric.c ***
t_dcolor		calculate_catadioptric_radiance(const t_world *world,
					t_intersection *intersection, const t_ray *ray,
					int recursion_level);

// *** catadioptric_utils.c ***
t_ray			get_reflection_ray(const t_catadioptric_vars *catadioptric_vars,
					const t_intersection *intersection);
t_ray			get_refraction_ray(const t_catadioptric_vars *catadioptric_vars,
					const t_intersection *intersection, const t_ray *ray);

#endif