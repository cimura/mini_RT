/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:33:07 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/21 16:41:11 by ttakino          ###   ########.fr       */
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
	int			size;

	size = ft_double_pointer_size(per_word_pointer);
	sphere = object_init();
	if (sphere == NULL)
		return (1);
	sphere->identifier = SPHERE;
	if (set_vector(&sphere->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (free(sphere), 1);
	if (set_dimension(&sphere->diameter, per_word_pointer[2], 0, -1) != 0)
		return (free(sphere), 1);
	if (material_register(&per_word_pointer[3], &sphere->material, SPHERE) != 0)
		return (free(sphere), 1);
	if (size > 4
		&& texture_register(&per_word_pointer[5], &sphere->textures) != 0)
		return (free(sphere), 1);
	return (add_object_to_lst(world, sphere));
}

int	parse_plane(t_world *world, char **per_word_pointer)
{
	t_object	*plane;
	int			size;

	size = ft_double_pointer_size(per_word_pointer);
	plane = object_init();
	if (plane == NULL)
		return (1);
	plane->identifier = PLANE;
	if (set_vector(&plane->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (free(plane), 1);
	if (set_vector(&plane->orientation_vec, per_word_pointer[2], -1, 1) != 0)
		return (free(plane), 1);
	if (normalize_checker(&plane->orientation_vec, per_word_pointer[2]) != 0)
		return (free(plane), 1);
	if (material_register(&per_word_pointer[3], &plane->material, PLANE) != 0)
		return (free(plane), 1);
	if (size > 4
		&& texture_register(&per_word_pointer[5], &plane->textures) != 0)
		return (free(plane), 1);
	return (add_object_to_lst(world, plane));
}

int	parse_cylinder(t_world *world, char **per_word_pointer)
{
	t_object	*cylinder;
	int			size;

	size = ft_double_pointer_size(per_word_pointer);
	cylinder = object_init();
	if (cylinder == NULL)
		return (1);
	cylinder->identifier = CYLINDER;
	if (set_vector(&cylinder->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (free(cylinder), 1);
	if (set_vector(&cylinder->orientation_vec, per_word_pointer[2], -1, 1) != 0)
		return (free(cylinder), 1);
	if (normalize_checker(&cylinder->orientation_vec, per_word_pointer[2]) != 0)
		return (free(cylinder), 1);
	if (set_dimension(&cylinder->diameter, per_word_pointer[3], 0, -1) != 0
		|| set_dimension(&cylinder->height, per_word_pointer[4], 0, -1) != 0)
		return (free(cylinder), 1);
	if (material_register(&per_word_pointer[5],
			&cylinder->material, CYLINDER) != 0)
		return (free(cylinder), 1);
	if (size > 6 && texture_register(&per_word_pointer[7],
			&cylinder->textures) != 0)
		return (free(cylinder), 1);
	return (add_object_to_lst(world, cylinder));
}
