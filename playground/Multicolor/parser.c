/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:16:36 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/17 14:48:04 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "draw.h"

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
	else if (errnum == INV_NUMBER)
		printf("%s: Invalid number.\n", arg);
	else if (errnum == OUT_OF_RANGE)
		printf("%s: Number out of range.\n", arg);
	else if (errnum == INV_PARAM)
		printf("%s: Invalid parameter.\n", arg);
	else if (errnum == NOT_MATCH_PARAM_NUM)
		printf("%s: The number of parameters does not match.\n", arg);
}

int	check_num_of_args(int argc)
{
	if (argc != 2)
	{
		print_err_msg(INV_NUM_OF_ARGS, NULL);
		return (1);
	}
	return (0);
}

int	check_file_name(char *filename)
{
	if (ft_strrncmp(filename, ".rt", 3) != 0)
	{
		print_err_msg(INV_FILENAME, filename);
		return (1);
	}
	return (0);
}

#define BUF_SIZE 1025

int	read_rt_file(char *filename, char *buf)
{
	int	fd;
	int	file_bytes;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_err_msg(FILE_NOT_FOUND, filename);
		return (1);
	}
	file_bytes = read(fd, buf, BUF_SIZE);
	if (file_bytes < 0)
	{
		print_err_msg(CANT_READ_FILE, filename);
		return (1);
	}
	if (file_bytes > BUF_SIZE - 1)
	{
		print_err_msg(FILE_TOO_LARGE, filename);
		return (1);
	}
	buf[file_bytes] = '\0';
	return (0);
}

void	free_double_pointer(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i] != NULL)
	{
		free(pointer[i]);
		pointer[i] = NULL;
		i++;
	}
	free(pointer);
}

int	parse_line(t_scene_data *scene, char *line)
{
	char	**per_word_pointer;
	int		status;

	status = 0;
	per_word_pointer = ft_split(line, ' ');
	if (per_word_pointer == NULL || per_word_pointer[0] == NULL)
		return (1);
	if (ft_strncmp(per_word_pointer[0], "A", 3) == 0)
		status = parse_ambient_lightning(scene, per_word_pointer);// parse_ambient_lightning
	else if (ft_strncmp(per_word_pointer[0], "C", 3) == 0)
		status = parse_camera(scene, per_word_pointer);// parse_camera
	else if (ft_strncmp(per_word_pointer[0], "L", 3) == 0)
		status = parse_light(scene, per_word_pointer);// parse_light
	else if (ft_strncmp(per_word_pointer[0], "sp", 3) == 0)
		;// parse_sphere
	else if (ft_strncmp(per_word_pointer[0], "pl", 3) == 0)
		;// parse_plane
	else if (ft_strncmp(per_word_pointer[0], "cy", 3) == 0)
		;// parse_cylinder
	else
		return (print_err_msg(INV_IDENTIFIER, per_word_pointer[0]), 1);
	free_double_pointer(per_word_pointer);
	return (status);
}

int	parse_rt_file(t_scene_data *scene, char *buf)
{
	char	**per_row_pointer;
	int		i;

	per_row_pointer = ft_split(buf, '\n');
	if (per_row_pointer == NULL)
		return (1);
	i = 0;
	while (per_row_pointer[i] != NULL)
	{
		// TODO t_sceneに当てはめる
		if (parse_line(scene, per_row_pointer[i]) != 0)
		{
			free_double_pointer(per_row_pointer);
			return (1);
		}
		i++;
	}
	printf ("%s\n", buf);
	free_double_pointer(per_row_pointer);
	return (0);
}

int	parse_arguments(t_scene_data *scene, int argc, char **argv)
{
	char	buf[BUF_SIZE];

	if (check_num_of_args(argc) != 0)
		return (1);
	// filename check
	if (check_file_name(argv[1]) != 0)
		return (1);
	// read file
	if (read_rt_file(argv[1], buf) != 0)
		return (1);
	// parse file
	if (parse_rt_file(scene, buf) != 0)
		return (1);
	// setup scene data from .rt file
	return (0);
}
