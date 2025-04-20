/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:59:53 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 13:45:15 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

static void	catadioptric_set(t_material *material, int material_id)
{
	material->use_perfect_reflectance = false;
	material->catadioptric_factor = dcolor_init(0.0, 0.0, 0.0);
	material->use_refraction = false;
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
	else if (material_id == WATER)
	{
		material->use_perfect_reflectance = true;
		material->catadioptric_factor = dcolor_init(1.0, 1.0, 1.0);
		material->use_refraction = true;
		material->refractive_index = 1.33;
	}
}

t_material	material_init(int material_id, t_dcolor color, int obj_id)
{
	t_material	material;

	material.diffuse = color;
	material.specular = specular_init(material_id);
	material.shinness = shinness_init(material_id);
	catadioptric_set(&material, material_id);
	if (obj_id == PLANE || obj_id == CYLINDER)
		material.use_thin_surfase = true;
	else
		material.use_thin_surfase = false;
	return (material);
}
