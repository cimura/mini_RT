/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:43:06 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/24 13:18:15 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		c -= 32;
	return (c);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (0);
// 	if (argv[1][1] != '\0')
// 		printf("Determine the first character of a string.\n");
// 	printf("%c\n", ft_toupper(argv[1][0]));
// 	return (0);
// }