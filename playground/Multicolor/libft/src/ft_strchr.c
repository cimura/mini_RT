/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:27:55 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/30 13:03:03 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	cst_c;

	cst_c = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == cst_c)
			return ((char *)&str[i]);
		i++;
	}
	if (cst_c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

//  #include <stdlib.h>
//  #include <stdio.h>
//  int	main(int argc, const char **argv)
//  {
//  	if (argc != 3)
//  		return (0);
// 	printf("ft_ = %s\n", ft_strchr(argv[1], argv[2][0]));
// 	printf("strchr = %s\n", strchr(argv[1], argv[2][0]));
//  	return (0);
//  }
