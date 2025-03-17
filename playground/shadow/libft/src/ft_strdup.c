/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:37:14 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/29 17:53:06 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	int		size;
	char	*result;
	int		i;

	i = 0;
	size = ft_strlen(string) + 1;
	result = (char *)malloc(size * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (string[i] != '\0')
	{
		result[i] = string[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*string = "Hello!!!";

// 	printf("%s\n", ft_strdup(string));
// 	return (0);
// }
