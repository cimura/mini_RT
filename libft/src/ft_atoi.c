/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:44:53 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/11 14:00:40 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_isspace(char check)
{
	if (check == ' ' || check == '\t' || check == '\n'
		|| check == '\v' || check == '\f' || check == '\r')
		return (1);
	return (0);
}

static int	check_overflow(int sign, long l, char c)
{
	if (sign == 1)
	{
		if (LONG_MAX / 10 < l
			|| (LONG_MAX / 10 == l && LONG_MAX % 10 < c - '0'))
			return (1);
	}
	else if (sign == -1)
	{
		if (LONG_MIN / -10 < l
			|| (LONG_MIN / -10 == l && LONG_MIN % -10 * -1 < c - '0'))
			return (-1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	while (check_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		if (check_overflow(sign, result, nptr[i]) == 1)
			return ((int)LONG_MAX);
		else if (check_overflow(sign, result, nptr[i]) == -1)
			return ((int)LONG_MIN);
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)result * sign);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (0);
// 	printf("ft_atoi = %d\n", ft_atoi(argv[1]));
// 	printf("atoi = %d\n", atoi(argv[1]));
// 	return (0);
// }