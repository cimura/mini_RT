/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:57:34 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/24 16:29:19 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cast_s;

	i = 0;
	cast_s = (unsigned char *)s;
	while (i < n)
	{
		if (cast_s[i] == (unsigned char)c)
			return ((void *)&cast_s[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*ft_s = "abcde";
// 	char	*s = "abcde";
// 	char	c = 'd';
// 	size_t	num = 5;
// 	printf("ft_戻り値 = %s\n", ft_memchr(ft_s, c, num));
// 	printf("-------------\n");
// 	printf("memchr戻り値 = %s\n", memchr(s, c, num));
// 	return (0);
// }