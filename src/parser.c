/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:16:36 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/25 20:08:39 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static int	check_num_of_args(int argc)
{
	if (argc != 2)
	{
		print_err_msg(INV_NUM_OF_ARGS, NULL);
		return (1);
	}
	return (0);
}

static int	check_file_name(char *filename)
{
	if (ft_strrncmp(filename, ".rt", 3) != 0)
	{
		print_err_msg(INV_FILENAME, filename);
		return (1);
	}
	return (0);
}

static int	read_rt_file(char *filename, char *buf)
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
		print_err_msg(FILE_NOT_FOUND, filename);
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

int	parse_arguments(t_world *world, int argc, char **argv)
{
	char	buf[BUF_SIZE];

	if (check_num_of_args(argc) != 0)
		return (1);
	if (check_file_name(argv[1]) != 0)
		return (1);
	if (read_rt_file(argv[1], buf) != 0)
		return (1);
	if (parse_rt_file(world, buf) != 0)
		return (1);
	return (0);
}
