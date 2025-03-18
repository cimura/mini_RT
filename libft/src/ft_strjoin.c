/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:59:15 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/12 16:03:02 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	s1_size;
	size_t	s2_size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	result = (char *)malloc((s1_size + s2_size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < s1_size || i <= s2_size)
	{
		if (i < s1_size)
			result[i] = s1[i];
		if (i <= s2_size)
		result[s1_size + s2_size - i] = s2[s2_size - i];
		i++;
	}
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s = ft_strjoin("tripouille", "42");
// 	printf ("%s\n", s);
// 	free(s);
// 	return (0);
// }
