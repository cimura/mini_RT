/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:59:58 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/19 18:25:29 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**get_values_double_pointer(char *src, int num)
{
	char	*no_brackets;
	char	**result;

	if (src == NULL)
		return (NULL);
	if (ft_char_count(src, ',') != num - 1)
		return (print_err_msg(INV_PARAM, src), NULL);
	no_brackets = src;
	if (no_brackets == NULL)
		return (NULL);
	result = ft_split(no_brackets, ',');
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

	rgb_str = get_values_double_pointer(str, 3);
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
int	set_vector(t_vector3 *xyz, char *str, double min, double max)
{
	char	**xyz_str;
	double	xyz_double[3];
	int		i;

	if (str == NULL)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, NULL), 1);
	xyz_str = get_values_double_pointer(str, 3);
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

int	set_dimension(double *value, char *str, double min, double max)
{
	if (str == NULL)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, str), 1);
	*value = ft_atod(str);
	if (min >= max)
		return (0);
	if (*value < min || *value > max)
		return (print_err_msg(OUT_OF_RANGE, str), 1);
	return (0);
}

// いろんな角度を試したいので引数は正規化することにする
int	normalize_checker(t_vector3 *vector, char *str)
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
