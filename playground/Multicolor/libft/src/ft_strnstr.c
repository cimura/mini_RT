/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:03:35 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/30 13:52:32 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)&haystack[0]);
	if (haystack == NULL && len == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j]
			&& needle[j] != '\0' && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// #include <stdlib.h>
// #include <stdio.h>
// int	main(void)
// {
// 	// if (argc != 4)
// 	// 	return (0);
// 	// printf("ft_ = %s\n", ft_strnstr(argv[1], argv[2], atoi(argv[3])));
// 	// printf("strstr = %s\n", strnstr(argv[1], argv[2], atoi(argv[3])));
// 	printf("ft_ = %s\n", ft_strnstr("", "coucou", -1));
// 	return (0);
// }