/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:59:58 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/08 21:58:53 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*remove_brackets(char *str)
{
	char	*result;
	char	len;
	int		i;

	len = ft_strlen(str);
	if (str[0] != '(' || str[len - 1] != ')' || len < 3)
		return (print_err_msg(INV_PARAM, str), NULL);
	result = malloc(len - 1);
	if (result == NULL)
		return (NULL);
	str++;
	i = 0;
	while (*str != ')' && i < len)
	{
		result[i] = *str;
		str++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

// str=(a,b,c...,n) -> extract_...(str, n);
static char	**extract_values_in_brackets(char *src, int num)
{
	char	*no_brackets;
	char	**result;

	if (src == NULL)
		return (NULL);
	if (ft_char_count(src, ',') != num - 1)
		return (print_err_msg(INV_PARAM, src), NULL);
	no_brackets = remove_brackets(src);
	if (no_brackets == NULL)
		return (NULL);
	result = ft_split(no_brackets, ',');
	free(no_brackets);
	if (result == NULL)
		return (NULL);
	if (ft_double_pointer_size(result) != num)
		return (print_err_msg(INV_PARAM, src), NULL);
	return (result);
}

//この関数は255,255,255のようなフォーマットを展開してrgbに登録する
int	set_rgb(t_dcolor *rgb, char *str)
{
	char		**rgb_str;
	double		rgb_double[3];
	int			i;

	rgb_str = extract_values_in_brackets(str, 3);
	if (rgb_str == NULL)
		return (1);
	i = 0;
	while (rgb_str[i] != NULL)
	{
		rgb_double[i] = ft_atoi(rgb_str[i]);
		if (rgb_double[i] < 0 || rgb_double[i] > 255)
			return (print_err_msg(OUT_OF_RANGE, rgb_str[i]), 1);
		i++;
	}
	rgb->red = rgb_double[0] / 255;
	rgb->green = rgb_double[1] / 255;
	rgb->blue = rgb_double[2] / 255;
	free_double_pointer((void **)rgb_str);
	return (0);
}

// この関数は座標やベクトル(x,y,zからなるもの)を構造体に登録する
// 範囲はminとmaxに。範囲がないときはminとmaxを同じ値に
int	set_vector(t_vector *xyz, char *str, double min, double max)
{
	char	**xyz_str;
	double	xyz_double[3];
	int		i;

	xyz_str = extract_values_in_brackets(str, 3);
	if (xyz_str == NULL)
		return (1);
	i = 0;
	while (xyz_str[i] != NULL)
	{
		xyz_double[i] = ft_atod(xyz_str[i]);
		if (min != max && (xyz_double[i] < min || xyz_double[i] > max))
			return (print_err_msg(OUT_OF_RANGE, xyz_str[i]), 1);
		i++;
	}
	xyz->x = xyz_double[0];
	xyz->y = xyz_double[1];
	xyz->z = xyz_double[2];
	free_double_pointer((void **)xyz_str);
	return (0);
}

// いろんな角度を試したいので引数は正規化することにする
int	normalize_checker(t_vector *vector, char *str)
{
	*vector = normalize_vector(*vector);
	(void)str;
	//if (pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2) != 1)
	//{
	//	print_err_msg(NOT_NORMALIZED_VEC, str);
	//	return (1);
	//}
	return (0);
}
