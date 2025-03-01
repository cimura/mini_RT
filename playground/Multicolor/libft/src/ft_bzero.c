/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:35:53 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/24 13:35:35 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cast_s;
	size_t			i;

	cast_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		cast_s[i] = 0;
		i++;
	}
}

// #include <stdio.h>
// int	main(void)
// {
// 	int	ft_dest[] = {1,2,3,4,5};
// 	int	dest[] = {1,2,3,4,5};
// 	int	i;
// 	size_t	num = 5 * sizeof(int);
// 	ft_bzero(ft_dest, num);
// 	printf("ft_dest = ");
// 	i = 0;
// 	while (i < 5)
// 	{
// 		printf("%d", ft_dest[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	i = 0;
// 	printf("---------------------\n");
// 	bzero(dest, num);
// 	i = 0;
// 	printf("dest = ");
// 	while (i < 5)
// 	{
// 		printf("%d", dest[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);
// }