#include "renderer.h"

static void	calculate_sphere_intersections_num(t_coef *coef, t_object sphere, t_ray ray)
{
	t_vector start_to_sphere;

	start_to_sphere = subst_vector(ray.coordinates_vec, sphere.coordinates_vec);
	coef->a = calculate_inner_product(ray.orientation_vec, ray.orientation_vec);
	coef->b = 2.0 * calculate_inner_product(start_to_sphere, ray.orientation_vec);
	coef->c = calculate_inner_product(start_to_sphere, start_to_sphere) - (sphere.diameter / 2.0) * (sphere.diameter / 2.0);
	coef->d = coef->b * coef->b - 4 * coef->a * coef->c;
}

void	set_sphere_intersection(t_intersection *i, t_object sphere, t_ray ray)
{
	t_coef			coef;
	t_intersection	i1;
	t_intersection	i2;

	calculate_sphere_intersections_num(&coef, sphere, ray);
	if (coef.d < 0)
		return ;
	i1.t = ((-1 * coef.b) - sqrt(coef.d)) / (2 * coef.a);
	i2.t = ((-1 * coef.b) + sqrt(coef.d)) / (2 * coef.a);
	if (i1.t > i2.t)
		swap_intersection(&i1, &i2);
	if (i2.t < 0)
		return ;
	i1.coordinates_vec = add_vector(ray.coordinates_vec,
		multi_vector(ray.orientation_vec, i1.t));
	i2.coordinates_vec = add_vector(ray.coordinates_vec,
		multi_vector(ray.orientation_vec, i2.t));
	i1.object = sphere;
	i2.object = sphere;
	if (i1.t >= 0)
		*i = i1;
	else if (i2.t >= 0)
		*i = i2;
}

t_vector	get_sphere_normal_vector(t_vector intersection, t_object sphere, t_ray ray)
{
	t_vector	normal_vector;
	double		ray_dot_normal;

	normal_vector = subst_vector(intersection, sphere.coordinates_vec);
	ray_dot_normal = calculate_inner_product(ray.orientation_vec, normal_vector);
	if (ray_dot_normal >= 0)
		normal_vector = multi_vector(normal_vector, -1);
	return (normalize_vector(normal_vector));
}
