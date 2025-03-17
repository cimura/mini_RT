/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:50:20 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/15 18:32:47 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '.')
		return (false);
	while (str[i] != '\0')
<<<<<<< HEAD:playground/Multicolor/libft/src/ft_strlen.c
=======
	{
		printf("%c", str[i]);
		if (str[i + 1] != '\0' && str[i] == '.')
		{
			i++;
			decimal_pointer_counter++;
		}
		if (decimal_pointer_counter > 1)
			return (false);
		if (!ft_isdigit(str[i]))
			return (false);
>>>>>>> ad29cdf (ambient_lightning構造体のparserが完成):playground/Multicolor/parse_objects.c
		i++;
	return (i);
}

<<<<<<< HEAD:playground/Multicolor/libft/src/ft_strlen.c
// #include <stdio.h>
// int	main(int argc, char** argv)
// {
// 	if (argc != 2)
// 		return (0);
// 	printf("%d\n", ft_strlen(argv[1]));
// 	return (0);
// }
=======
//この関数は255,255,255のようなフォーマットを展開してrgbに登録する
int	register_rgb(t_rgb *rgb, char *str)
{
	char	**rgb_str;
	int		rgb_int[3];
	int		i;

	if (str == NULL)
		return (1);
	rgb_str = ft_split(str, ',');
	if (rgb_str == NULL)
		return (1);
	if (ft_double_pointer_size(rgb_str) != 3)
		return (print_err_msg(INV_ARGUMENT, str), 1);
	i = 0;
	while (rgb_str[i] != NULL)
	{
		rgb_int[i] = ft_atoi(rgb_str[i]);
		if (rgb_int[i] < 0 || rgb_int[i] > 255)
		return (print_err_msg(OUT_OF_RANGE, rgb_str[i]), 1);
		i++;
	}
	rgb->red = rgb_int[0] / 255;
	rgb->green = rgb_int[1] / 255;
	rgb->blue = rgb_int[2] / 255;
	free_double_pointer(rgb_str);
	return (0);
}

int	parse_ambient_lightning(t_scene_data *scene, char **per_word_pointer)
{
	t_ambient_lightning	ambient_lightning;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 3)
		return (print_err_msg(INV_ARGUMENT, NULL), 1);
	ambient_lightning.identifier = per_word_pointer[0];
	if (!is_valid_double(per_word_pointer[1]))
		return (print_err_msg(INV_NUMBER, per_word_pointer[1]), 1);
	ambient_lightning.ratio = ft_atod(per_word_pointer[1]);
	if (ambient_lightning.ratio < 0.0 || ambient_lightning.ratio > 1.0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[1]), 1);
	//if (!ft_isdigit(per_word_pointer[2]))
	//	return (print_err_msg(INV_NUMBER, per_word_pointer[2]), 1);
	if (register_rgb(&ambient_lightning.rgb, per_word_pointer[2]) != 0)
		return (1);
	printf("ratio: %lf\n", ambient_lightning.ratio);
	printf("red: %lf, green: %lf, blue: %lf\n", ambient_lightning.rgb.red, ambient_lightning.rgb.green, ambient_lightning.rgb.blue);
	scene->ambient_lightning = ambient_lightning;
	return (0);
}
>>>>>>> ad29cdf (ambient_lightning構造体のparserが完成):playground/Multicolor/parse_objects.c
