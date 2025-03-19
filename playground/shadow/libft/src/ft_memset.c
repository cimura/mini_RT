/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:36:28 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/24 13:18:23 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*cast_s;
	size_t	i;

	i = 0;
	cast_s = (char *)s;
	while (i < n)
	{
		cast_s[i] = c;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	ft_dest[100];
// 	char	dest[100];
// 	char	s = 'a';
// 	size_t	num = 100;
// 	ft_memset(ft_dest, s, num);
// 	printf("ft_dest = %s\n", ft_dest);
// 	printf("-------------\n");
// 	memset(dest, s, num);
// 	printf("dest = %s\n", dest);
// 	return (0);
// }
