/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:50:25 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/12 14:33:56 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	unsigned char	*get;
	size_t			i;

	if (n == 0 || size == 0)
		return (malloc(1));
	if (n > INT_MAX / size)
		return (NULL);
	get = (unsigned char *)malloc(n * size);
	if (get == NULL)
		return (NULL);
	i = 0;
	while (i < n * size)
	{
		get[i] = 0;
		i++;
	}
	return ((void *)get);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int	*field;
// 	int	n;
// 	int	i;

// 	n = 10;
// 	field = (int *)ft_calloc(n, sizeof(int));
// 	if (field == NULL)
// 	{
// 		printf("Could not allocate memory.");
// 		return (0);
// 	}
// 	i = 0;
// 	while (i < n)
// 	{
// 		printf("%d", field[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	free(field);
// 	return (0);
// }

// #include <limits.h>

// int main(void){
// 	int	num = INT_MIN;
// 	printf("%zu\n", (size_t)num);
// }

// 18446744073709551615
// 18446744071562067968