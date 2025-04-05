/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:37 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/24 23:00:39 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <stdbool.h>
# include "libft.h"

// *** libft2.c *** utils.hなどに移してもいいかも
double	ft_atod(char *nptr);
int     ft_strrncmp(const char *s1, const char *s2, size_t size);
int		ft_double_pointer_size(char **pointers);

// *** libft3.c *** utils.hなどに移してもいいかも
int		ft_char_count(char *src, char target);

// *** utils.c ***
void	swap_double(double *a, double *b);
// double型の変数を範囲内に落とし込む関数 (min <= max)
void	double_compressor(double *d, double min, double max);
void	free_double_pointer(char **pointer);
bool	ft_is_valid_double(char *str);
bool	ft_is_valid_int(char *str);

#endif