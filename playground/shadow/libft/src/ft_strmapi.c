/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:36:25 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/12 16:04:41 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			s_len;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	result = (char *)malloc((s_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[s_len] = '\0';
	i = 0;
	while (i < s_len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}

// char	my_func(unsigned int n, char c)
// {
// 	return (c + n);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s;
// 	s = ft_strmapi("0000000000", my_func);
// 	if (s == NULL)
// 		printf("NULL\n");
// 	printf("s\t=\t%s\n", s);
// 	free(s);
// 	return (0);
// }
