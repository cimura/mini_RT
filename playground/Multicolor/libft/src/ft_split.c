/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:39:39 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/12 16:04:10 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**make_str(char const *s, char c)
{
	char	**result;
	int		i;
	int		flag;
	int		count;

	i = 0;
	flag = 1;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			flag = 1;
		else if (flag == 1)
		{
			flag = 0;
			count++;
		}
		i++;
	}
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[count] = NULL;
	return (result);
}

static char	*make_word(char const *s, char c, int start)
{
	char	*str;
	int		i;

	i = 0;
	while (s[start + i] != c && s[start + i] != '\0')
		i++;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	while (0 < i)
	{
		str[i - 1] = s[start + (i - 1)];
		i--;
	}
	return (str);
}

static char	**free_words(int result_i, char **result)
{
	result_i--;
	while (0 < result_i)
	{
		free(result[result_i]);
		result_i--;
	}
	free(result);
	return (NULL);
}

static char	**apply_word(char const *s, char c, char **result)
{
	int		flag;
	int		result_i;
	int		s_i;

	flag = 1;
	result_i = 0;
	s_i = 0;
	while (s[s_i] != '\0')
	{
		if (s[s_i] == c || s[s_i] == '\0')
			flag = 1;
		else if (flag == 1)
		{
			result[result_i] = make_word(s, c, s_i);
			if (result[result_i] == NULL)
				return (free_words(result_i, result));
			else
			{
				s_i += ft_strlen(result[result_i++]) - 1;
				flag = 0;
			}
		}
		s_i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (s == NULL)
		return (NULL);
	result = make_str(s, c);
	if (result == NULL)
		return (NULL);
	result = apply_word(s, c, result);
	if (result == NULL)
		return (NULL);
	return (result);
}

// int	main(void)
// {
// 	char	**split = ft_split("hellozs", 'z');
// 	int		i = 0;
// 	while (split[i] != NULL)
// 	{
// 		printf("%s\n", split[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (split[i] != NULL)
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// 	return (0);
// }
