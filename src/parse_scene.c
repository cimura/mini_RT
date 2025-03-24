/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takat <takat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:56:46 by takat             #+#    #+#             */
/*   Updated: 2025/03/24 22:56:54 by takat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_ambient_lightning(t_world *world, char **per_word_pointer)
{
	t_ambient_lightning	ambient_lightning;
	double				ratio;
	t_dcolor			rgb;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 3)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	if (world->ambient_lightning.identifier)
		return (print_err_msg(TOO_MANY_PARAM, per_word_pointer[0]), 1);
	ambient_lightning.identifier = AMBIENT_LIGHTNING;
	if (!ft_is_valid_double(per_word_pointer[1]))
		return (print_err_msg(INV_NUMBER, per_word_pointer[1]), 1);
	ratio = ft_atod(per_word_pointer[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[1]), 1);
	if (set_rgb(&rgb, per_word_pointer[2]) != 0)
		return (1);
	ambient_lightning.intensity = dcolor_coef_multi(rgb, ratio);
	world->ambient_lightning = ambient_lightning;
	return (0);
}

int	parse_camera(t_world *world, char **per_word_pointer)
{
	t_camera	camera;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 4)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	if (world->camera.identifier)
		return (print_err_msg(TOO_MANY_PARAM, per_word_pointer[0]), 1);
	camera.identifier = CAMERA;
	if (set_vector(&camera.coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (1);
	if (set_vector(&camera.orientation_vec, per_word_pointer[2], -1, 1) != 0)
		return (1);
	if (normalize_checker(&camera.orientation_vec, per_word_pointer[2]) != 0)
		return (1);
	if (!ft_is_valid_int(per_word_pointer[3]))
		return (print_err_msg(INV_NUMBER, per_word_pointer[3]), 1);
	camera.horizontal_fov = ft_atoi(per_word_pointer[3]);
	if (camera.horizontal_fov < 0 || camera.horizontal_fov > 180)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[3]), 1);
	world->camera = camera;
	return (0);
}

int	parse_light(t_world *world, char **per_word_pointer)
{
	t_light		light;
	double		ratio;
	t_dcolor	rgb;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 4)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	if (world->light.identifier)
		return (print_err_msg(TOO_MANY_PARAM, per_word_pointer[0]), 1);
	light.identifier = LIGHT;
	if (set_vector(&light.coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (1);
	ratio = ft_atod(per_word_pointer[2]);
	if (ratio < 0.0 || ratio > 1.0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[2]), 1);
	if (set_rgb(&rgb, per_word_pointer[3]) != 0)
		return (1);
	light.intensity = dcolor_coef_multi(rgb, ratio);
	world->light = light;
	return (0);
}
