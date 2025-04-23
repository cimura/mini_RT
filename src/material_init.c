/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:59:53 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/23 15:21:14 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "parser.h"

static t_dcolor	specular_init(int material_id)
{
	t_dcolor	specular;

	specular = dcolor_init(0.0, 0.0, 0.0);
	if (material_id == GLASS)
		specular = dcolor_init(0.7, 0.7, 0.7);
	else if (material_id == IRON)
		specular = dcolor_init(0.8, 0.8, 0.8);
	else if (material_id == SILVER)
		specular = dcolor_init(1.0, 1.0, 1.0);
	else if (material_id == WOOD)
		specular = dcolor_init(0.15, 0.15, 0.15);
	else if (material_id == WATER)
		specular = dcolor_init(0.85, 0.85, 0.85);
	return (specular);
}

static double	shinness_init(int material_id)
{
	double	shinness;

	shinness = 0.0;
	if (material_id == GLASS)
		shinness = 90;
	else if (material_id == IRON)
		shinness = 75;
	else if (material_id == SILVER)
		shinness = 150;
	else if (material_id == WOOD)
		shinness = 15;
	else if (material_id == WATER)
		shinness = 65;
	return (shinness);
}

static t_dcolor	catadioptric_factor_init(t_material *material,
	int material_id)
{
	t_dcolor	catadioptric_factor;

	catadioptric_factor = dcolor_init(0, 0, 0);
	if (material_id == GLASS)
		catadioptric_factor = dcolor_init(1.0, 1.0, 1.0);
	else if (material_id == IRON)
		catadioptric_factor = dcolor_init(0, 0, 0);
	else if (material_id == SILVER)
		catadioptric_factor = dcolor_init(1.0, 1.0, 1.0);
	else if (material_id == WOOD)
		catadioptric_factor = dcolor_init(0, 0, 0);
	else if (material_id == WATER)
		catadioptric_factor = dcolor_init(1.0, 1.0, 1.0);
	if (catadioptric_factor.red == 0 && catadioptric_factor.green == 0
		&& catadioptric_factor.blue == 0)
		material->use_perfect_reflectance = false;
	else
		material->use_perfect_reflectance = true;
	return (catadioptric_factor);
}

static double	refractive_index_init(t_material *material, int material_id)
{
	double	refractive_index;

	refractive_index = 1.0;
	if (material_id == GLASS)
		refractive_index = 1.51;
	else if (material_id == IRON)
		refractive_index = 1.0;
	else if (material_id == SILVER)
		refractive_index = 1.0;
	else if (material_id == WOOD)
		refractive_index = 1.0;
	else if (material_id == WATER)
		refractive_index = 1.33;
	if (refractive_index == 1.0)
		material->use_refraction = false;
	else
		material->use_refraction = true;
	return (refractive_index);
}

t_material	material_init(int material_id, t_dcolor color, int obj_id)
{
	t_material	material;

	material.diffuse = color;
	material.original_diffuse = color;
	material.specular = specular_init(material_id);
	material.shinness = shinness_init(material_id);
	material.catadioptric_factor
		= catadioptric_factor_init(&material, material_id);
	material.refractive_index = refractive_index_init(&material, material_id);
	if (obj_id == PLANE || obj_id == CYLINDER)
		material.use_thin_surfase = true;
	else
		material.use_thin_surfase = false;
	material.textures = NULL;
	return (material);
}
