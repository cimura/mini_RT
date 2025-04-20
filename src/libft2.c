/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:11:44 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:46:36 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>

static int	check_isspace(char check)
{
	if (check == ' ' || check == '\t' || check == '\n'
		|| check == '\v' || check == '\f' || check == '\r')
		return (1);
	return (0);
}

static double	update_result(char **nptr, double result, double *factor)
{
	while ('0' <= **nptr && **nptr <= '9')
	{
		result = result * 10 + (**nptr - '0');
		if (factor != NULL)
			*factor *= 10;
		(*nptr)++;
	}
	return (result);
}

double	ft_atod(char *nptr)
{
	int		sign;
	double	factor;
	double	result;

	sign = 1;
	if (nptr == NULL)
		return (-1);
	while (check_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	factor = 1.0;
	result = 0.0;
	result = update_result(&nptr, result, NULL);
	if (*nptr == '.')
		nptr++;
	result = update_result(&nptr, result, &factor);
	return ((double)result * sign / factor);
}

int	ft_strrncmp(const char *s1, const char *s2, size_t size)
{
	int	i;
	int	j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (--size && i && j && s1[i] == s2[j])
	{
		i--;
		j--;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

int	ft_double_pointer_size(char **pointers)
{
	int	size;

	if (pointers == NULL)
		return (0);
	size = 0;
	while (pointers[size] != NULL)
		size++;
	return (size);
}
