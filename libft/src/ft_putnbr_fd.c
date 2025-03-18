/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:50:06 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/24 12:50:16 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits_putn(int n)
{
	int	digits;

	digits = 0;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static int	ten_exponentiation(int digits)
{
	int	answer;

	answer = 1;
	while (0 < (digits - 1))
	{
		answer *= 10;
		digits--;
	}
	return (answer);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		digits;
	char	num;

	digits = get_digits_putn(n);
	if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
		write(fd, "-", 1);
	while (0 < digits)
	{
		if (0 < n)
			num = '0' + (n / ten_exponentiation(digits));
		else
			num = '0' - (n / ten_exponentiation(digits));
		write(fd, &num, 1);
		n = n % ten_exponentiation(digits);
		digits--;
	}
}

// int	main(void)
// {
// 	ft_putnbr_fd(-2147483648, 1);
// 	write(1, "\n", 1);
// 	return (0);
// }
