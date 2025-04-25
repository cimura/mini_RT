/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:16:38 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/25 20:07:55 by ttakino          ###   ########.fr       */
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
	INV_IDENTIFIER,
	INV_NUMBER,
	OUT_OF_RANGE,
	INV_PARAM,
	NOT_MATCH_PARAM_NUM,
	NOT_NORMALIZED_VEC,
	TOO_MANY_PARAM,
};

// *** parser.c ***
void	print_err_msg(int errnum, char *arg);
void	free_double_pointer(char **pointer);

// *** parse_objects.c ***
int		parse_ambient_lightning(t_world *scene, char **per_word_pointer);
int		parse_camera(t_world *scene, char **per_word_pointer);
int		parse_light(t_world *scene, char **per_word_pointer);
int		parse_sphere(t_world *world, char **per_word_pointer);
int		parse_plane(t_world *world, char **per_word_pointer);
int		parse_cylinder(t_world *world, char **per_word_pointer);

// *** libft2.c *** utils.hなどに移してもいいかも
double	ft_atod(char *nptr);
int     ft_strrncmp(const char *s1, const char *s2, size_t size);
int		ft_double_pointer_size(char **pointers);

// *** libft3.c *** utils.hなどに移してもいいかも
int		ft_char_count(char *src, char target);

#endif