/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:47:21 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/29 17:28:09 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// #include <stdlib.h>
// #include <stdio.h>
// int	main(int argc, const char **argv)
// {
// 	size_t	num;
// 	if (argc != 4)
// 		return (0);
// 	num = atoi(argv[3]);	
// 	printf("ft_... = %d\n", ft_strncmp(argv[1], argv[2], num));
// 	printf("strncmp = %d\n", strncmp(argv[1], argv[2], num));
// 	return (0);
// }