/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:40:35 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/25 20:05:41 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	write_err_msg(char *arg)
{
	write(STDERR_FILENO, arg, ft_strlen(arg));
}

void	print_err_msg(int errnum, char *arg)
{
	if (arg == NULL)
		arg = "";
	write_err_msg("Error\n");
	write_err_msg(arg);
	if (errnum == INV_NUM_OF_ARGS)
		write_err_msg("Too many/too few arguments.\n");
	else if (errnum == FILE_TOO_LARGE)
		write_err_msg(".rt file is too large.\n");
	else if (errnum == INV_FILENAME)
		write_err_msg("The argument file extension must be .rt.\n");
	else if (errnum == FILE_NOT_FOUND)
		write_err_msg("File not found.\n");
	else if (errnum == INV_IDENTIFIER)
		write_err_msg("Invalid identifier.\n");
	else if (errnum == OUT_OF_RANGE)
		write_err_msg("Number out of range.\n");
	else if (errnum == INV_PARAM)
		write_err_msg("Invalid parameter.\n");
	else if (errnum == NOT_MATCH_PARAM_NUM)
		write_err_msg("The number of parameters does not match.\n");
	else if (errnum == NOT_NORMALIZED_VEC)
		write_err_msg("This vector is not normalized\n");
	else if (errnum == TOO_MANY_PARAM)
		write_err_msg("This parameter cannot be fefined multiple times.\n");
}

static int	parse_line(t_world *world, char *line)
{
	char	**per_word_pointer;
	int		status;

	status = 0;
	per_word_pointer = ft_split(line, ' ');
	if (per_word_pointer == NULL || per_word_pointer[0] == NULL)
		return (1);
	if (ft_strncmp(per_word_pointer[0], "sk", 3) == 0)
		status = parse_skybox(world, per_word_pointer);
	else if (ft_strncmp(per_word_pointer[0], "A", 3) == 0)
		status = parse_ambient_lightning(world, per_word_pointer);
	else if (ft_strncmp(per_word_pointer[0], "C", 3) == 0)
		status = parse_camera(world, per_word_pointer);
	else if (ft_strncmp(per_word_pointer[0], "L", 3) == 0)
		status = parse_light(world, per_word_pointer);
	else if (ft_strncmp(per_word_pointer[0], "sp", 3) == 0)
		status = parse_sphere(world, per_word_pointer);
	else if (ft_strncmp(per_word_pointer[0], "pl", 3) == 0)
		status = parse_plane(world, per_word_pointer);
	else if (ft_strncmp(per_word_pointer[0], "cy", 3) == 0)
		status = parse_cylinder(world, per_word_pointer);
	else
		return (print_err_msg(INV_IDENTIFIER, per_word_pointer[0]), 1);
	free_double_pointer((void **)per_word_pointer);
	return (status);
}

int	parse_rt_file(t_world *world, char *buf)
{
	char	**per_row_pointer;
	int		i;

	per_row_pointer = ft_split(buf, '\n');
	if (per_row_pointer == NULL)
		return (1);
	i = 0;
	while (per_row_pointer[i] != NULL)
	{
		if (parse_line(world, per_row_pointer[i]) != 0)
		{
			free_double_pointer((void **)per_row_pointer);
			world_destroy(world);
			return (1);
		}
		i++;
	}
	free_double_pointer((void **)per_row_pointer);
	return (0);
}
