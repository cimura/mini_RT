/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:45:23 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/29 17:35:25 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				i;
	const char		*save;
	unsigned char	cst_c;

	i = 0;
	save = NULL;
	cst_c = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == cst_c)
			save = &str[i];
		i++;
	}
	if (cst_c == '\0')
		return ((char *)&str[i]);
	return ((char *)save);
}

// #include <stdlib.h>
// #include <stdio.h>
// int	main(int argc, const char **argv)
// {
// 	if (argc != 3)
// 		return (0);
// 	printf("ft_ = %s\n", ft_strrchr(argv[1], argv[2][0]));
// 	printf("strrchr = %s\n", strrchr(argv[1], argv[2][0]));
// 	return (0);
// }