/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:22 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/24 23:00:24 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

// double型の変数を範囲内に落とし込む関数 (min <= max)
void	double_compressor(double *d, double min, double max)
{
	if (*d < min)
		*d = min;
	if (*d > max)
		*d = max;
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

bool	ft_is_valid_double(char *str)
{
	int	i;
	int	decimal_pointer_counter;

	decimal_pointer_counter = 0;
	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '.')
		return (false);
	while (str[i] != '\0')
	{
		if (str[i + 1] != '\0' && str[i] == '.')
		{
			i++;
			decimal_pointer_counter++;
		}
		if (decimal_pointer_counter > 1)
			return (false);
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_is_valid_int(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
