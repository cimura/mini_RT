/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:40:35 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/10 17:19:20 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_err_msg(int errnum, char *arg)
{
	if (arg == NULL)
		arg = "";
	printf("Error\n");
	if (errnum == INV_NUM_OF_ARGS)
		printf("%s: Too many/too few arguments.\n", arg);
	else if (errnum == FILE_TOO_LARGE)
		printf("%s: .rt file is too large.\n", arg);
	else if (errnum == INV_FILENAME)
		printf("%s: The argument file extension must be .rt.\n", arg);
	else if (errnum == FILE_NOT_FOUND)
		printf("%s: File not found.\n", arg);
	else if (errnum == CANT_READ_FILE)
		printf("%s: Cannot read file.\n", arg);
	else if (errnum == INV_IDENTIFIER)
		printf("%s: Invalid identifier.\n", arg);
	else if (errnum == OUT_OF_RANGE)
		printf("%s: Number out of range.\n", arg);
	else if (errnum == INV_PARAM)
		printf("%s: Invalid parameter.\n", arg);
	else if (errnum == NOT_MATCH_PARAM_NUM)
		printf("%s: The number of parameters does not match.\n", arg);
	else if (errnum == NOT_NORMALIZED_VEC)
		printf("%s: This vector is not normalized\n", arg);
	else if (errnum == TOO_MANY_PARAM)
		printf("%s: This parameter cannot be fefined multiple times.\n", arg);
}

static int	parse_line(t_world *world, char *line)
{
	char	**per_word_pointer;
	int		status;

	status = 0;
	per_word_pointer = ft_split(line, ' ');
	if (per_word_pointer == NULL || per_word_pointer[0] == NULL)
		return (1);
	if (ft_strncmp(per_word_pointer[0], "A", 3) == 0)
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
	printf ("%s\n", buf);
	free_double_pointer((void **)per_row_pointer);
	return (0);
}
