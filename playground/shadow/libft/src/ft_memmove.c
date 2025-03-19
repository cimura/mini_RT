/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:31:07 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/12 15:04:21 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move(unsigned char *dst, const unsigned char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst < src)
	{
		while (i < n)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		while (0 < n)
		{
			dst[n - 1] = src[n - 1];
			n--;
		}
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*cast_dst;
	const unsigned char	*cast_src;

	cast_dst = (unsigned char *)dest;
	cast_src = (const unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	move(cast_dst, cast_src, n);
	return (dest);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	ft_dest[100];
// 	char	dest[100];
// 	char	*src = "Hello";
// 	size_t	num = 1;
// 	memset(ft_dest, '\0', 100);
// 	memset(dest, '\0', 100);
// 	printf("ft_dest = %s\n", ft_dest);
// 	printf("src = %s\n", src);
// 	ft_memmove(ft_dest, src, num);
// 	printf("new ft_dest = %s\n", ft_dest);
// 	printf("-------------\n");
// 	printf("dest = %s\n", dest);
// 	printf("src = %s\n", src);
// 	memmove(dest, src, num);
// 	printf("new dest = %s\n", dest);
// 	return (0);
// }