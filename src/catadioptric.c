/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catadioptric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:23:24 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/29 00:10:40 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static t_ray	get_reflection_ray(t_intersection intersection,
	t_vector inverce_ray_vec, double inverce_ray_dot_normal, t_world world)
{
	t_ray	rfl_ray;

	rfl_ray.orientation_vec = normalize_vector(subst_vector(multi_vector(
		intersection.normal_vec, inverce_ray_dot_normal * 2), inverce_ray_vec));
	rfl_ray.coordinates_vec = add_vector(intersection.coordinates_vec,
		multi_vector(rfl_ray.orientation_vec, EPSILON));
	(void)world;
	//rfl_ray.prev_refractive_index = world.global_refraction_index;
	return (rfl_ray);
}

static t_ray	get_refraction_ray(double rfr_1_2, double omega,
	t_intersection intersection, t_ray ray)
{
	t_ray	rfr_ray;

	rfr_ray.orientation_vec = normalize_vector(subst_vector(multi_vector(
		ray.orientation_vec, rfr_1_2), multi_vector(
		intersection.normal_vec, rfr_1_2 * omega)));
	rfr_ray.coordinates_vec = add_vector(intersection.coordinates_vec,
		multi_vector(rfr_ray.orientation_vec, EPSILON));
	//rfr_ray.prev_refractive_index = intersection.object.material.refractive_index;
	return (rfr_ray);
}

static bool	is_object_in_trajectory(t_object object, t_list **src_lst)
{
	t_list		*lst;
	//t_object	*lst_object;

	//lst = trajectory.refractive_indexs;
	lst = *src_lst;
	while (lst != NULL)
	{
		//lst_object = (t_object *)lst->content;
		if (*(double *)lst->content == object.material.refractive_index)
			return (true);
		lst = lst->next;
	}
	return (false);
}

static void	delete_node_same_id(t_list **src_lst, double id)
{
	//t_object	lst_object;
	t_list		*lst;
	t_list		*prev;

	lst = *src_lst;
	prev = NULL;
	while (lst != NULL)
	{
		//lst_object = *(t_object *)lst->content;
		if (*(double *)lst->content == id)
		{
			if (prev)
				prev->next = lst->next;
			else
				*src_lst = lst->next;
			ft_lstdelone(lst, NULL);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
}

t_dcolor	calculate_catadioptric_radiance(t_world world, t_intersection intersection,
	t_trajectory trajectory, int recursion_level)
{
	t_dcolor		color;
	t_trajectory	rfl_trajectory;
	//t_trajectory	rfr_trajectory;
	//t_ray			rfl_ray;
	t_ray			rfr_ray;
	double			refraction_index1;
	double			refraction_index2;
	t_vector		inverce_ray_vec;
	double			inverce_ray_dot_normal;
	double			rfr_2_1;
	double			cos1;
	double			cos2;
	double			omega;
	double			p_polarized_light;
	double			s_polarized_light;
	double			reflectance_index;
	//t_object		trajectory_lst_content;
	//bool			ray_from_back;

	//ray_from_back = false;
	color = dcolor_init(0, 0, 0);
	//if (intersection.object.material.use_perfect_reflectance == false)
	//	return (color);
	inverce_ray_vec = multi_vector(trajectory.ray.orientation_vec, -1);
	inverce_ray_dot_normal = calculate_inner_product(inverce_ray_vec,
		intersection.normal_vec);

	rfl_trajectory.ray =
		get_reflection_ray(intersection, inverce_ray_vec, inverce_ray_dot_normal, world);
	(void)rfl_trajectory;
	//ft_lstadd_front(&rfl_trajectory.refractive_indexs, ft_lstnew(trajectory.refractive_indexs->content));
	//color =
	//	dcolor_multi(ray_trace_recursive(world, rfl_trajectory,
	//	recursion_level + 1), intersection.object.material.catadioptric_factor);
	//ft_lstclear(&rfl_trajectory.refractive_indexs, NULL);
	if (intersection.object.material.use_refraction == false)
		return (color);
	//trajectory_lst_content = *(t_object *)trajectory.refractive_indexs->content;
	refraction_index1 = *(double *)(trajectory.refractive_indexs)->content;
	refraction_index2 = intersection.object.material.refractive_index;
	if (is_object_in_trajectory(intersection.object, &trajectory.refractive_indexs) == true)
	{
		//color = dcolor_add(color, dcolor_init(100,0,0));
		delete_node_same_id(&trajectory.refractive_indexs, intersection.object.material.refractive_index);
		//trajectory_lst_content = *(t_object *)trajectory.refractive_indexs->content;
		refraction_index2 = *(double *)trajectory.refractive_indexs->content;
		//printf("%lf ", refraction_index2);
	}
	else
	{
		ft_lstadd_front(&trajectory.refractive_indexs, ft_lstnew(&intersection.object.material.refractive_index));
	}
	rfr_2_1 = refraction_index2 / refraction_index1;
	cos1 = inverce_ray_dot_normal;
	cos2 = (refraction_index1 / refraction_index2)
		* sqrt(pow(rfr_2_1, 2) - (1 - pow(cos1, 2)));
	omega = rfr_2_1 * cos2 - cos1;
	rfr_ray = get_refraction_ray(refraction_index1 / refraction_index2, omega,
		intersection, trajectory.ray);
	p_polarized_light = (rfr_2_1 * cos1 - cos2) / (rfr_2_1 * cos1 + cos2);
	s_polarized_light = -1 * omega / (rfr_2_1 * cos2 + cos1);
	reflectance_index = (pow(p_polarized_light, 2) + pow(s_polarized_light, 2)) / 2;
	//color = dcolor_coef_multi(color, reflectance_index);
	trajectory.ray = rfr_ray;
	color = dcolor_add(color, dcolor_coef_multi(dcolor_multi(ray_trace_recursive(world, trajectory,
		recursion_level + 1),
		intersection.object.material.catadioptric_factor), 1.0 - reflectance_index));
	return (color);
}
