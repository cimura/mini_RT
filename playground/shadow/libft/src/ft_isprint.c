/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:43:22 by ttakino           #+#    #+#             */
/*   Updated: 2024/04/24 13:18:29 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (' ' <= c && c <= '~')
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int	main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		return (0);
// 	if (argv[1][1] != '\0')
// 		printf("Determine the first character of a string.\n");
// 	printf("%d\n", ft_isprint(argv[1][0]));
// 	return (0);
// }