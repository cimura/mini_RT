#include "renderer.h"

//　外積を計算して点が三角形平面の内部にあるかを判定
static bool	point_in_triangle(t_object triangle, t_vector intersection)
{
	t_vector v0 = subst_vector(triangle.vertex.v2, triangle.vertex.v1);
	t_vector v1 = subst_vector(triangle.vertex.v3, triangle.vertex.v1);
	t_vector v2 = subst_vector(intersection, triangle.vertex.v1);

	double dot00 = calculate_inner_product(v0, v0);
	double dot01 = calculate_inner_product(v0, v1);
	double dot02 = calculate_inner_product(v0, v2);
	double dot11 = calculate_inner_product(v1, v1);
	double dot12 = calculate_inner_product(v1, v2);
	double inv_denom = 1.0 / (dot00 * dot11 - dot01 * dot01);
	double u = (dot11 * dot02 - dot01 * dot12) * inv_denom;
	double v = (dot00 * dot12 - dot01 * dot02) * inv_denom;

	return (u >= 0 && v >= 0 && (u + v) <= 1);
}


void	set_triangle_intersection(t_intersection *i, t_object triangle, t_ray ray)
{
	t_vector	triangle_to_start;
	double		pts_dot_po;
	double		dir_dot_po;

	triangle_to_start = subst_vector(ray.coordinates_vec, triangle.coordinates_vec);
	pts_dot_po = calculate_inner_product(triangle_to_start, triangle.orientation_vec);
	dir_dot_po = calculate_inner_product(ray.orientation_vec, triangle.orientation_vec);
	if (dir_dot_po == 0)
		return ;
	i->t = -pts_dot_po / dir_dot_po;
	if (i->t < 0)
		return ;
	i->coordinates_vec = add_vector(ray.coordinates_vec, multi_vector(ray.orientation_vec, i->t));
	if (!point_in_triangle(triangle, i->coordinates_vec))
		return ;
	i->object = triangle;
}

t_vector	get_triangle_normal_vector(t_vector intersection, t_object triangle, t_ray ray)
{
	t_vector	normal_vector;
	t_vector	v1;
	t_vector	v2;
	double		ray_dot_normal;

	(void)intersection;
	v1 = subst_vector(triangle.vertex.v2, triangle.vertex.v1);
	v2 = subst_vector(triangle.vertex.v3, triangle.vertex.v1);
	normal_vector = cross_product(v1, v2);
	normal_vector = normalize_vector(normal_vector);

	// レイが法線と同じ向きなら反転
	ray_dot_normal = calculate_inner_product(ray.orientation_vec, normal_vector);
	if (ray_dot_normal < 0)
		normal_vector = multi_vector(normal_vector, -1);
	printf("get triangle normal vec\n");
	return (normal_vector);
}
