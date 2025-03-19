/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:31:22 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/29 17:54:10 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(int argc, char **argv)
// {
// 	char	ft_dest[10];
// 	char	dest[10];
// 	const char	*src;
// 	size_t	size;
// 	src = argv[1];
// 	size = atoi(argv[2]);
// 	if (argc != 3)
// 		return (0);
// 	printf("ft_戻り値 = %zu\n", ft_strlcpy(ft_dest, src, size));
// 	printf("ft_dest = %s\n", ft_dest);
// 	printf("strlcpy戻り値 = %lu\n", strlcpy(dest, src, size));
// 	printf("dest = %s\n", dest);
// 	return (0);
// }