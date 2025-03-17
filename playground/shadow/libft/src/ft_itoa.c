/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:01:22 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/11 14:05:40 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits_itoa(int n)
{
	int	digits;

	digits = 0;
	if (n <= 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		digits;

	digits = get_digits_itoa(n);
	result = (char *)malloc(digits + 1);
	if (result == NULL)
		return (NULL);
	result[digits] = '\0';
	result[0] = '0';
	if (n == 0)
		return (result);
	while (n != 0)
	{
		if (0 < n)
			result[digits - 1] = '0' + (n % 10);
		else
			result[digits - 1] = '0' - (n % 10);
		digits--;
		n /= 10;
	}
	if (digits != 0)
		result[0] = '-';
	return (result);
}

// #include <limits.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*n;
// 	n = ft_itoa(INT_MIN);
// 	printf("%s\n", n);
// 	free(n);
// 	return (0);
// }
