/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:02:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/29 18:02:25 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_size;
	size_t	src_size;
	size_t	i;

	if (dest == NULL && size == 0)
		return (ft_strlen(src));
	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	if (size <= dest_size)
		return (size + src_size);
	i = 0;
	while (i < size - dest_size - 1 && src[i] != '\0')
	{
		dest[dest_size + i] = src[i];
		i++;
	}
	dest[dest_size + i] = '\0';
	return (dest_size + src_size);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(int argc, char **argv)
// {
// 	char	ft_dest[20] = "12345";
// 	char	dest[20] = "12345";
// 	char	*src;
// 	size_t	size;
// 	if (argc != 3)
// 		return (0);
// 	src = argv[1];
// 	size = atoi(argv[2]);
// 	printf("ft_dest = %s\n", ft_dest);
// 	printf("ft_戻り値 = %zu\n", ft_strlcat(ft_dest, src, size));
// 	printf("cat後ft_dest = %s\n", ft_dest);
// 	printf("--------------------------------\n");
// 	printf("dest = %s\n", dest);
// 	printf("strlcat戻り値 = %lu\n", strlcat(dest, src, size));
// 	printf("cat後dest = %s\n", dest);
// 	return (0);
// }