/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:39:02 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/23 15:22:43 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "parser.h"

void	material_destroy(t_material *material)
{
	ft_lstclear(&material->textures, texture_destroy);
}

#define ID_NOT_FOUND 2

static int	set_material_id(int *material_id, char *material_name)
{
	*material_id = WOOD;
	if (material_name == NULL)
		return (ID_NOT_FOUND);
	if (ft_strncmp(material_name, "GLASS", 6) == 0)
		*material_id = GLASS;
	else if (ft_strncmp(material_name, "IRON", 5) == 0)
		*material_id = IRON;
	else if (ft_strncmp(material_name, "SILVER", 7) == 0)
		*material_id = SILVER;
	else if (ft_strncmp(material_name, "WOOD", 5) == 0)
		*material_id = WOOD;
	else if (ft_strncmp(material_name, "WATER", 6) == 0)
		*material_id = WATER;
	else
		return (ID_NOT_FOUND);
	return (0);
}

int	material_register(char **per_word_pointer, t_material *material,
	int obj_identifier)
{
	int			material_id;
	t_dcolor	color;
	int			next_index;

	if (per_word_pointer[0] == NULL)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, NULL), 1);
	if (set_rgb(&color, per_word_pointer[0]) != 0)
		return (1);
	next_index = 2;
	if (set_material_id(&material_id, per_word_pointer[1]) == ID_NOT_FOUND)
		next_index = 1;
	*material = material_init(material_id, color, obj_identifier);
	if (texture_register(&per_word_pointer[next_index],
			&material->textures) != 0)
		return (1);
	return (0);
}
