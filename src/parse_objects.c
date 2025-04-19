/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:33:07 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/19 17:05:01 by sshimura         ###   ########.fr       */
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

static char	*remove_double_quotes(char *str)
{
	char	*result;
	char	len;
	int		i;

	len = ft_strlen(str);
	if (str[0] != '\"' || str[len - 1] != '\"' || len < 3)
		return (print_err_msg(INV_PARAM, str), NULL);
	result = malloc(len - 1);
	if (result == NULL)
		return (NULL);
	str++;
	i = 0;
	while (*str != '\"' && i < len)
	{
		result[i] = *str;
		str++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

t_texture	*init_new_texture(char *filename)
{
	t_texture	*tex;
	int			identifier;
	char		*no_quotes;

	if (ft_strncmp(filename, "N:", 2) == 0)
		identifier = NORMAL;
	else if (ft_strncmp(filename, "C:", 2) == 0)
		identifier = COLOR;
	else
		return (print_err_msg(INV_PARAM, filename), NULL);
	if (ft_strlen(filename) <= ft_strlen("S:\"\""))
		return (print_err_msg(INV_PARAM, filename), NULL);
	no_quotes = remove_double_quotes(&filename[ft_strlen("S:")]);
	if (no_quotes == NULL)
		return (NULL);
	tex = malloc(sizeof(t_texture));
	if (tex == NULL)
		return (NULL);
	if (load_texture(tex, no_quotes, identifier) != 0)
		return (free(tex), free(no_quotes),
		print_err_msg(FILE_NOT_FOUND, no_quotes), NULL);
	free(no_quotes);
	return (tex);
}

int	texture_register(char **filenames, t_list **lst)
{
	t_texture	*tex;
	t_list		*node;
	int			i;

	*lst = NULL;
	i = 0;
	while (filenames[i] != NULL)
	{
		tex = init_new_texture(filenames[i]);
		if (tex == NULL)
			return (1);
		node = ft_lstnew(tex);
		if (node == NULL)
			return (free(tex), 1);
		ft_lstadd_front(lst, node);
		i++;
	}
	return (0);
}

int	material_register(char **per_word_pointer, t_material *material,
	int obj_identifier)
{
	int			material_id;
	t_dcolor	color;

	// printf("per_word_pointer[0]: %s\n", per_word_pointer[0]);
	if (per_word_pointer[0] == NULL || ft_double_pointer_size(per_word_pointer) < 1)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, NULL), 1);
	
	if (set_rgb(&color, per_word_pointer[0]) != 0)
		return (1);
	// if (per_word_pointer[1] == NULL)
	printf("[1] -> %s\n", per_word_pointer[1]);
	if (ft_strncmp(per_word_pointer[1], "GLASS", ft_strlen("GLASS") + 1) == 0)
		material_id = GLASS;
	else if (ft_strncmp(per_word_pointer[1], "IRON", ft_strlen("IRON") + 1) == 0)
		material_id = IRON;
	else if (ft_strncmp(per_word_pointer[1], "SILVER", ft_strlen("SILVER") + 1) == 0)
		material_id = SILVER;
	else if (ft_strncmp(per_word_pointer[1], "WOOD", ft_strlen("WOOD") + 1) == 0)
		material_id = WOOD;
	else if (ft_strncmp(per_word_pointer[1], "WATER", ft_strlen("WATER") + 1) == 0)
		material_id = WATER;
	else
		material_id = WOOD;
	printf("out\n");
		// else
	// 	return (print_err_msg(INV_IDENTIFIER, per_word_pointer[1]), 1);
	*material = material_init(material_id, color, obj_identifier);
	return (0);
}

int	parse_sphere(t_world *world, char **per_word_pointer)
{
	t_object	*sphere;
	t_dcolor	color;

	sphere = malloc(sizeof(t_object));
	if (sphere == NULL)
		return (1);
	sphere->identifier = SPHERE;
	if (set_vector(&sphere->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (free(sphere), 1);
	sphere->diameter = ft_atod(per_word_pointer[2]);
	if (sphere->diameter < 0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[2]), free(sphere), 1);
	if (material_register(&per_word_pointer[3], &sphere->material, SPHERE) != 0)
		return (free(sphere), 1);
	if (texture_register(&per_word_pointer[5], &sphere->textures) != 0)
		return (free(sphere), 1);
	return (add_object_to_lst(world, sphere));
}

int	parse_plane(t_world *world, char **per_word_pointer)
{
	t_object	*plane;
	t_dcolor	color;

	int	i = 0;
	while (per_word_pointer[i] != NULL)
		printf("-%s\n", per_word_pointer[i++]);
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
	if (material_register(&per_word_pointer[3], &plane->material, PLANE) != 0)
		return (free(plane), 1);
	if (texture_register(&per_word_pointer[5], &plane->textures) != 0)
		return (free(plane), 1);
	return (add_object_to_lst(world, plane));
}

int	parse_cylinder(t_world *world, char **per_word_pointer)
{
	t_object	*cylinder;
	t_dcolor	color;

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
		return (print_err_msg(INV_PARAM, per_word_pointer[3]), free(cylinder), 1);
	cylinder->height = ft_atod(per_word_pointer[4]);
	if (cylinder->height < 0)
		return (print_err_msg(INV_PARAM, per_word_pointer[4]), free(cylinder), 1);
	if (material_register(&per_word_pointer[5], &cylinder->material, CYLINDER) != 0)
		return (free(cylinder), 1);
	if (texture_register(&per_word_pointer[7], &cylinder->textures) != 0)
		return (free(cylinder), 1);
	return (add_object_to_lst(world, cylinder));
}
