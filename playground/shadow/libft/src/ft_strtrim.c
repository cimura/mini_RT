/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:37:34 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/12 16:07:05 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	count_result_len(char const *s1, char const *set, size_t s1_len)
{
	size_t	i;
	size_t	end_i;
	size_t	count;

	i = 0;
	end_i = s1_len;
	count = 0;
	while (check_set(s1[i], set) == 1)
	{
		count++;
		i++;
	}
	while (check_set(s1[end_i - 1], set) == 1 && i < end_i)
	{
		count++;
		end_i--;
	}
	return (s1_len - count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	result_len;
	size_t	result_i;
	size_t	s1_i;

	if (s1 == NULL)
		return (NULL);
	result_len = count_result_len(s1, set, ft_strlen(s1));
	result = (char *)malloc(result_len + 1);
	if (result == NULL)
		return (NULL);
	result[result_len] = '\0';
	result_i = 0;
	s1_i = 0;
	while (check_set(s1[s1_i], set) == 1)
		s1_i++;
	while (result_i < result_len)
	{
		result[result_i] = s1[s1_i];
		result_i++;
		s1_i++;
	}
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*string = ft_strtrim("  \t \t \n   \n\n\n\t", " \n\t");
// 	printf("%s\n", string);
// 	free(string);
// }
