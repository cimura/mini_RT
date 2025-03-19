/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:17:59 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/30 13:34:13 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*cast_dst;
	const unsigned char	*cast_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	cast_dst = (unsigned char *)dest;
	cast_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*cast_dst++ = *cast_src++;
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char	ft_dest[1];
// 	char	dest[1];
// 	char	*src = "Hello";
// 	size_t	num = 7;
// 	memset(ft_dest, '\0', 1);
// 	memset(dest, '\0', 1);
// 	printf("ft_dest = %s\n", ft_dest);
// 	printf("src = %s\n", src);
// 	ft_memcpy(ft_dest, src, num);
// 	printf("new ft_dest = %s\n", ft_dest);
// 	printf("-------------\n");
// 	printf("dest = %s\n", dest);
// 	printf("src = %s\n", src);
// 	memcpy(dest, src, num);
// 	printf("new dest = %s\n", dest);
// 	return (0);
// }
