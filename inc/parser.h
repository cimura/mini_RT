/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:16:38 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/21 16:31:56 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "mini_rt.h"

# define BUF_SIZE 10000

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

// *** parser.c ***
void		print_err_msg(int errnum, char *arg);

// *** parser_utils.c ***
void		print_err_msg(int errnum, char *arg);
int			parse_rt_file(t_world *world, char *buf);

// *** parse_objects_utils.c ***
int			set_rgb(t_dcolor *rgb, char *str);
int			set_vector(t_vector3 *xyz, char *str, double min, double max);
int			set_dimension(double *value, char *str, double min, double max);
int			normalize_checker(t_vector3 *vector, char *str);

// *** parse_objects.c ***
int			parse_ambient_lightning(t_world *world, char **per_word_pointer);
int			parse_camera(t_world *world, char **per_word_pointer);
int			parse_light(t_world *world, char **per_word_pointer);

// *** parse_scene.c ***
int			parse_skybox(t_world *world, char **per_word_pointer);
int			parse_sphere(t_world *world, char **per_word_pointer);
int			parse_plane(t_world *world, char **per_word_pointer);
int			parse_cylinder(t_world *world, char **per_word_pointer);

#endif