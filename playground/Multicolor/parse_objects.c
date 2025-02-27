/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:33:07 by ttakino           #+#    #+#             */
/*   Updated: 2025/02/26 16:58:58 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	ft_is_valid_double(char *str)
{
	int	i;
	int	decimal_pointer_counter;

	decimal_pointer_counter = 0;
	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '.')
		return (false);
	while (str[i] != '\0')
	{
		if (str[i + 1] != '\0' && str[i] == '.')
		{
			i++;
			decimal_pointer_counter++;
		}
		if (decimal_pointer_counter > 1)
			return (false);
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_is_valid_int(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

//この関数は255,255,255のようなフォーマットを展開してrgbに登録する
int	register_rgb(t_rgb *rgb, char *str)
{
	char	**rgb_str;
	int		rgb_int[3];
	int		i;

	if (str == NULL)
		return (1);
	if (ft_char_count(str, ',') != 2)
		return (print_err_msg(INV_PARAM, str), 1);
	rgb_str = ft_split(str, ',');
	if (rgb_str == NULL)
		return (1);
	if (ft_double_pointer_size(rgb_str) != 3)
		return (print_err_msg(INV_PARAM, str), 1);
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

// この関数は座標やベクトル(x,y,zからなるもの)を構造体に登録する
// 範囲はminとmaxに。範囲がないときはminとmaxを同じ値に
int	register_xyz(t_vector *xyz, char *str, double min, double max)
{
	char	**xyz_str;
	double	xyz_int[3];
	int		i;

	if (str == NULL)
		return (1);
	if (ft_char_count(str, ',') != 2)
		return (print_err_msg(INV_PARAM, str), 1);
	xyz_str = ft_split(str, ',');
	if (xyz_str == NULL)
		return (1);
	if (ft_double_pointer_size(xyz_str) != 3)
		return (print_err_msg(INV_PARAM, str), 1);
	i = 0;
	while (xyz_str[i] != NULL)
	{
		xyz_int[i] = ft_atod(xyz_str[i]);
		if (min != max && (xyz_int[i] < min || xyz_int[i] > max))
			return (print_err_msg(OUT_OF_RANGE, xyz_str[i]), 1);
		i++;
	}
	xyz->x = xyz_int[0];
	xyz->y = xyz_int[1];
	xyz->z = xyz_int[2];
	free_double_pointer(xyz_str);
	return (0);
}

int	parse_ambient_lightning(t_scene_data *scene, char **per_word_pointer)
{
	t_ambient_lightning	ambient_lightning;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 3)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, NULL), 1);
	ambient_lightning.identifier = "A";
	if (!ft_is_valid_double(per_word_pointer[1]))
		return (print_err_msg(INV_NUMBER, per_word_pointer[1]), 1);
	ambient_lightning.ratio = ft_atod(per_word_pointer[1]);
	if (ambient_lightning.ratio < 0.0 || ambient_lightning.ratio > 1.0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[1]), 1);
	//if (!ft_isdigit(per_word_pointer[2]))
	//	return (print_err_msg(INV_NUMBER, per_word_pointer[2]), 1);
	if (register_rgb(&ambient_lightning.rgb, per_word_pointer[2]) != 0)
		return (1);
	printf("identifier: %s\n", ambient_lightning.identifier);
	printf("ratio: %lf\n", ambient_lightning.ratio);
	printf("red: %lf, green: %lf, blue: %lf\n", ambient_lightning.rgb.red, ambient_lightning.rgb.green, ambient_lightning.rgb.blue);
	scene->ambient_lightning = ambient_lightning;
	return (0);
}

int	parse_camera(t_scene_data *scene, char **per_word_pointer)
{
	t_camera	camera;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 4)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, NULL), 1);
	camera.identifier = "C";
	if (register_xyz(&camera.coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (1);
	if (register_xyz(&camera.orientation_vec, per_word_pointer[2], -1, 1) != 0)
		return (1);
	if (!ft_is_valid_int(per_word_pointer[3]))
		return (print_err_msg(INV_NUMBER, per_word_pointer[3]), 1);
	camera.horizontal_fov = ft_atoi(per_word_pointer[3]);
	if (camera.horizontal_fov < 0 || camera.horizontal_fov > 180)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[3]), 1);
	printf("identifier: %s\n", camera.identifier);
	printf("coordinates_vec: x=%lf y=%lf z=%lf\n", camera.coordinates_vec.x, camera.coordinates_vec.y, camera.coordinates_vec.z);
	printf("orientation_vec: x=%lf y=%lf z=%lf\n", camera.orientation_vec.x, camera.orientation_vec.y, camera.orientation_vec.z);
	printf("horizonal_fov: %d\n", camera.horizontal_fov);
	scene->camera = camera;
	return (0);
}

int	parse_light(t_scene_data *scene, char **per_word_pointer)
{
	t_light	light;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 4)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, NULL), 1);
	light.identifier = "L";
	if (register_xyz(&light.coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (1);
	light.ratio = ft_atod(per_word_pointer[2]);
	if (light.ratio < 0.0 || light.ratio > 1.0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[2]), 1);
	if (register_rgb(&light.rgb, per_word_pointer[3]) != 0)
		return (1);
	printf("identifier: %s\n", light.identifier);
	printf("coordinates_vec: x=%lf y=%lf z=%lf\n", light.coordinates_vec.x, light.coordinates_vec.y, light.coordinates_vec.z);
	printf("ratio: %lf\n", light.ratio);
	printf("red: %lf, green: %lf, blue: %lf\n", light.rgb.red, light.rgb.green, light.rgb.blue);
	scene->light = light;
	return (0);
}
