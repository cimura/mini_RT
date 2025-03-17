/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:22:07 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/12 16:01:40 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*pullout(char *result, char const *s, unsigned int start, size_t n)
{
	size_t	i;

	i = 0;
	while (s[start + i] != '\0' && i < n)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= (size_t)start || len == 0)
	{
		result = (char *)malloc(1);
		result[0] = '\0';
		return (result);
	}
	else if (start + len < s_len)
		result = (char *)malloc(len + 1);
	else
		result = (char *)malloc(s_len - start + 1);
	if (result == NULL)
		return (NULL);
	result = pullout(result, s, start, len);
	return (result);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*string;
// 	string = ft_substr("Hello", 1, 4);
// 	printf("%s\n", string);
// 	free(string);
// 	return (0);
// }
