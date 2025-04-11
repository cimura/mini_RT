/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:33:07 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/11 23:08:42 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_object_to_lst(t_world *world, t_object *object)
{
	t_list	*node;

	node = ft_lstnew(object);
	if (node == NULL)
		return (1);
	ft_lstadd_back(&world->objects, node);
	return (0);
}

int	parse_sphere(t_world *world, char **per_word_pointer)
{
	t_object	*sphere;
	t_dcolor	color;

	//if (ft_double_pointer_size(per_word_pointer) != 4)
	//	return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	sphere = malloc(sizeof(t_object));
	if (sphere == NULL)
		return (1);
	sphere->identifier = SPHERE;
	if (set_vector(&sphere->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (free(sphere), 1);
	sphere->diameter = ft_atod(per_word_pointer[2]);
	if (sphere->diameter < 0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[2]), free(sphere), 1);
	if (set_rgb(&color, per_word_pointer[3]) != 0)
		return (free(sphere), 1);
	sphere->material = material_init(WOOD, color);
	sphere->textures = NULL;
	if (per_word_pointer[4] && texture_register(&per_word_pointer[4], &sphere->textures) != 0)
		return (print_err_msg(INV_FILENAME, per_word_pointer[4]), free(sphere), 1);
	// 屈折の実装のため
	//if (ft_lstsize(world->objects) == 0)
	//{
	//	sphere->material = material_init(SILVER, color);
	//	printf("silver\n");
	//}
	//else if (ft_lstsize(world->objects) == 1)
	//{
	//	sphere->material = material_init(GLASS, color);
	//	printf("glass\n");
	//}
	//else if (ft_lstsize(world->objects) == 2)
	//{
	//	sphere->material = material_init(WATER, color);
	//	printf("water\n");
	//}
	// ここまで
	sphere->material.use_thin_surfase = false;
	return (add_object_to_lst(world, sphere));
}

int	parse_plane(t_world *world, char **per_word_pointer)
{
	t_object	*plane;
	t_dcolor	color;

	if (ft_double_pointer_size(per_word_pointer) != 4)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	plane = malloc(sizeof(t_object));
	if (plane == NULL)
		return (1);
	plane->identifier = PLANE;
	if (set_vector(&plane->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (free(plane), 1);
	if (set_vector(&plane->orientation_vec, per_word_pointer[2], -1, 1) != 0)
		return (free(plane), 1);
	if (normalize_checker(&plane->orientation_vec, per_word_pointer[2]) != 0)
		return (free(plane), 1);
	if (set_rgb(&color, per_word_pointer[3]) != 0)
		return (free(plane), 1);
	plane->material = material_init(WOOD, color);
	plane->textures = NULL;
	// デバッグ用
	//if (ft_lstsize(world->objects) == 1)
	//{
	//	plane->material = material_init(WATER, color);
	//}
	// ここまで
	plane->material.use_thin_surfase = true;
	return (add_object_to_lst(world, plane));
}

int	parse_cylinder(t_world *world, char **per_word_pointer)
{
	t_object	*cylinder;
	t_dcolor	color;

	if (ft_double_pointer_size(per_word_pointer) != 6)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	cylinder = malloc(sizeof(t_object));
	if (cylinder == NULL)
		return (1);
	cylinder->identifier = CYLINDER;
	if (set_vector(&cylinder->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (free(cylinder), 1);
	if (set_vector(&cylinder->orientation_vec, per_word_pointer[2], -1, 1) != 0)
		return (free(cylinder), 1);
	if (normalize_checker(&cylinder->orientation_vec, per_word_pointer[2]) != 0)
		return (free(cylinder), 1);
	cylinder->diameter = ft_atod(per_word_pointer[3]);
	if (cylinder->diameter < 0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[3]), free(cylinder), 1);
	cylinder->height = ft_atod(per_word_pointer[4]);
	if (cylinder->height < 0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[4]), free(cylinder), 1);
	if (set_rgb(&color, per_word_pointer[5]) != 0)
		return (free(cylinder), 1);
	cylinder->material = material_init(GLASS, color);
	cylinder->material.use_thin_surfase = true;
	cylinder->textures = NULL;
	return (add_object_to_lst(world, cylinder));
}
