/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:59:53 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/26 22:22:01 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_dcolor	specular_init(int material_id)
{
	t_dcolor	specular;

	if (material_id == GLASS)
		specular = dcolor_init(0.7, 0.7, 0.7);
	else if (material_id == IRON)
		specular = dcolor_init(0.8, 0.8, 0.8);
	else if (material_id == SILVER)
		specular = dcolor_init(1.0, 1.0, 1.0);
	else if (material_id == WOOD)
		specular = dcolor_init(0.15, 0.15, 0.15);
	return (specular);
}

static double	shinness_init(int material_id)
{
	double	shinness;

	if (material_id == GLASS)
		shinness = 90;
	else if (material_id == IRON)
		shinness = 75;
	else if (material_id == SILVER)
		shinness = 150;
	else if (material_id == WOOD)
		shinness = 15;
	return (shinness);
}

static void	catadioptric_set(t_material *material, int material_id)
{
	if (material_id == SILVER)
	{
		material->use_perfect_reflectance = true;
		material->catadioptric_factor = dcolor_init(1.0, 1.0, 1.0);
		material->use_refraction = false;
	}
	else if (material_id == GLASS)
	{
		material->use_perfect_reflectance = true;
		material->catadioptric_factor = dcolor_init(1.0, 1.0, 1.0);
		material->use_refraction = true;
		material->refractive_index = 1.51;
	}
	else
	{
		material->use_perfect_reflectance = false;
		material->catadioptric_factor = dcolor_init(0.0, 0.0, 0.0);
		material->use_refraction = false;
	}
}

t_material	material_init(int material_id, t_dcolor color)
{
	t_material	material;

	material.diffuse = color;
	material.specular = specular_init(material_id);
	material.shinness = shinness_init(material_id);
	catadioptric_set(&material, material_id);
	return (material);
}
