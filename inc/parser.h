/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:16:38 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/24 23:00:49 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "mini_rt.h"

enum	e_errnum
{
	INV_NUM_OF_ARGS,
	INV_FILENAME,
	FILE_TOO_LARGE,
	FILE_NOT_FOUND,
	CANT_READ_FILE,
	INV_IDENTIFIER,
	INV_NUMBER,
	OUT_OF_RANGE,
	INV_PARAM,
	NOT_MATCH_PARAM_NUM,
	NOT_NORMALIZED_VEC,
	TOO_MANY_PARAM,
};

// *** material.c ***
t_material	material_init(int material_id, t_dcolor color);

// *** parser.c ***
void		print_err_msg(int errnum, char *arg);
void		free_double_pointer(char **pointer);

// *** parse_objects_utils.c ***
int			set_rgb(t_dcolor *rgb, char *str);
int			set_vector(t_vector *xyz, char *str, double min, double max);
int			normalize_checker(t_vector *vector, char *str);

// *** parse_objects.c ***
int			parse_ambient_lightning(t_world *world, char **per_word_pointer);
int			parse_camera(t_world *world, char **per_word_pointer);
int			parse_light(t_world *world, char **per_word_pointer);

// *** parse_scene.c ***
int			parse_sphere(t_world *world, char **per_word_pointer);
int			parse_plane(t_world *world, char **per_word_pointer);
int			parse_cylinder(t_world *world, char **per_word_pointer);


#endif