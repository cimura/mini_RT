/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:40:34 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/21 16:41:29 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_object	*object_init(void)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (new == NULL)
		return (NULL);
	new->identifier = 0;
	new->coordinates_vec = init_vector(0, 0, 0);
	new->orientation_vec = init_vector(0, 0, 0);
	new->diameter = 0;
	new->height = 0;
	new->textures = NULL;
	return (new);
}

void	object_destroy(void *pointer)
{
	t_object	*object;

	object = (t_object *)pointer;
	ft_lstclear(&object->textures, texture_destroy);
	free(pointer);
}
