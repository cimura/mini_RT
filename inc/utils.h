#ifndef UTILS_H

# define UTILS_H

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

#endif