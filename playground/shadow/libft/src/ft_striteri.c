/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:51:05 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/12 16:06:24 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t		i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// void	my_func(unsigned int n, char *s)
// {
// 	*s += n;
// }

// int	main(void)
// {
// 	char	s[] = "000000";

// 	ft_striteri(s, my_func);
// 	printf("Modified string: %s\n", s);
// 	return (0);
// }
