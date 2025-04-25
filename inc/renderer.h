/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:40 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/25 19:45:25 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H

# define RENDERER_H

# include "mini_rt.h"
# include "vector.h"
# include "texture.h"

# define MAX_RECURSIVE_LEVEL 6

# define SCREEN_WIDTH 2.0
# define SCREEN_HEIGHT 2.0

# define BACKGROUND_COLOR_RED 0
# define BACKGROUND_COLOR_GREEN 0
# define BACKGROUND_COLOR_BLUE 0


typedef struct s_ray
{
	t_vector3	coordinates_vec;
	t_vector3	orientation_vec;
	double		prev_refractive_index;
}	t_ray;

typedef struct s_coefficient
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_coefficient;

typedef struct s_intersection
{
	double		t;
	bool		hit_on_back;
	t_vector3	coordinates_vec;
	t_vector3	normal_vec;
	t_object	*object;
}	t_intersection;

// *** camera.c ***
void			init_camera(t_camera *camera);

// *** sphere.c ***
void			set_sphere_intersection(t_intersection *i, t_object *sphere,
					const t_ray *ray);
void			set_sphere_normal_vector(t_intersection *intersection,
					const t_object *sphere, const t_ray *ray);
t_vector2	get_vec2_on_sphere(const t_intersection *intersection,
					const t_object *sphere);

// *** plane.c ***
void			set_plane_intersection(t_intersection *i, t_object *plane,
					const t_ray *ray);
void			set_plane_normal_vector(t_intersection *intersection,
					const t_object *plane, const t_ray *ray);
t_vector2		get_vec2_on_plane(const t_intersection *intersection,
					const t_object *plane, t_texture *tex);

// *** cylinder.c ***
void			set_cylinder_intersection(t_intersection *i, t_object *cylinder,
					const t_ray *ray);
void			set_cylinder_normal_vector(t_intersection *intersection,
					const t_object *cylinder, const t_ray *ray);
t_vector2		get_vec2_on_cylinder(const t_intersection *intersection,
					const t_object *cylinder, t_texture *tex);

// *** cylinder_utils.c ***
void			calculate_cylinder_intersections_num(t_coefficient *coef,
					const t_object *cylinder, const t_ray *ray);

/// *** intersections.c ***
void			swap_intersection(t_intersection *i1, t_intersection *i2);
t_intersection	find_intersection_minimum_distance(t_world world,
					const t_ray *ray);
void			calculate_intersections_normal_vector(t_intersection *i,
					const t_ray *ray);

// *** skybox.c ***
t_dcolor		apply_skybox(const t_world *world, const t_ray *ray);

// *** texture_mapping.c ***
void			texture_mapping(t_list *tex_lst, t_intersection *i);

// *** renderer.c ***
t_dcolor		ray_trace_recursive(const t_world *world, const t_ray *ray,
					int recursion_level);

#endif