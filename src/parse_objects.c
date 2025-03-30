/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:33:07 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/30 12:52:08 by cimy             ###   ########.fr       */
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

static char	*remove_brackets(char *str)
{
	char	*result;
	char	len;
	int		i;

	len = ft_strlen(str);
	if (str[0] != '(' || str[len - 1] != ')' || len < 3)
		return (print_err_msg(INV_PARAM, str), NULL);
	result = malloc(len - 2);
	if (result == NULL)
		return (NULL);
	str++;
	i = 0;
	while (*str != ')' && *str != '\0')
	{
		result[i] = *str;
		str++;
		i++;
	}
	return (result);
}

static char	**split_values(char *str)
{
	char	*no_brackets;
	char	**result;

	if (str == NULL)
	return (NULL);
	if (ft_char_count(str, ',') != 2)
		return (print_err_msg(INV_PARAM, str), NULL);
	no_brackets = remove_brackets(str);
	if (no_brackets == NULL)
		return (NULL);
	result = ft_split(no_brackets, ',');
	free(no_brackets);
	if (result == NULL)
		return (NULL);
	if (ft_double_pointer_size(result) != 3)
		return (print_err_msg(INV_PARAM, str), NULL);
	return (result);
}

//この関数は255,255,255のようなフォーマットを展開してrgbに登録する
int	set_rgb(t_dcolor *rgb, char *str)
{
	char		**rgb_str;
	double		rgb_double[3];
	int			i;

	rgb_str = split_values(str);
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
	free_double_pointer(rgb_str);
	return (0);
}

// この関数は座標やベクトル(x,y,zからなるもの)を構造体に登録する
// 範囲はminとmaxに。範囲がないときはminとmaxを同じ値に
int	set_vector(t_vector *xyz, char *str, double min, double max)
{
	char	**xyz_str;
	double	xyz_double[3];
	int		i;

	xyz_str = split_values(str);
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
	free_double_pointer(xyz_str);
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

int	add_object_to_lst(t_world *world, t_object *object)
{
	t_list	*node;

	node = ft_lstnew(object);
	if (node == NULL)
		return (ft_lstclear(&world->objects, NULL), 1);
	ft_lstadd_back(&world->objects, node);
	return (0);
}

t_material	init_material(t_dcolor diffuse_coef, t_dcolor specular_coef, double shinness,
	t_dcolor perfect_reflectance_coef)
{
	t_material	material;

	material.diffuse_coef = diffuse_coef;
	material.specular_coef = specular_coef;
	material.shinness = shinness;
	material.use_perfect_reflectance = false;
	if (perfect_reflectance_coef.red > 0 || perfect_reflectance_coef.green > 0
		|| perfect_reflectance_coef.blue > 0)
		material.use_perfect_reflectance = true;
	material.perfect_reflectance = perfect_reflectance_coef;
	return (material);
}

int	parse_ambient_lightning(t_world *world, char **per_word_pointer)
{
	t_ambient_lightning	ambient_lightning;
	double				ratio;
	t_dcolor				rgb;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 3)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	if (world->ambient_lightning.identifier)
		return (print_err_msg(TOO_MANY_PARAM, per_word_pointer[0]), 1);
	ambient_lightning.identifier = AMBIENT_LIGHTNING;
	if (!ft_is_valid_double(per_word_pointer[1]))
		return (print_err_msg(INV_NUMBER, per_word_pointer[1]), 1);
	ratio = ft_atod(per_word_pointer[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[1]), 1);
	if (set_rgb(&rgb, per_word_pointer[2]) != 0)
		return (1);
	ambient_lightning.intensity = dcolor_coef_multi(rgb, ratio);
	world->ambient_lightning = ambient_lightning;
	return (0);
}

int	parse_camera(t_world *world, char **per_word_pointer)
{
	t_camera	camera;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 4)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	if (world->camera.identifier)
		return (print_err_msg(TOO_MANY_PARAM, per_word_pointer[0]), 1);
	camera.identifier = CAMERA;
	if (set_vector(&camera.coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (1);
	if (set_vector(&camera.orientation_vec, per_word_pointer[2], -1, 1) != 0)
		return (1);
	if (normalize_checker(&camera.orientation_vec, per_word_pointer[2]) != 0)
		return (1);
	if (!ft_is_valid_int(per_word_pointer[3]))
		return (print_err_msg(INV_NUMBER, per_word_pointer[3]), 1);
	camera.horizontal_fov = ft_atoi(per_word_pointer[3]);
	if (camera.horizontal_fov < 0 || camera.horizontal_fov > 180)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[3]), 1);
	world->camera = camera;
	return (0);
}

int	parse_light(t_world *world, char **per_word_pointer)
{
	t_light	light;
	double	ratio;
	t_dcolor	rgb;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 4)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	if (world->light.identifier)
		return (print_err_msg(TOO_MANY_PARAM, per_word_pointer[0]), 1);
	light.identifier = LIGHT;
	if (set_vector(&light.coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (1);
	ratio = ft_atod(per_word_pointer[2]);
	if (ratio < 0.0 || ratio > 1.0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[2]), 1);
	if (set_rgb(&rgb, per_word_pointer[3]) != 0)
		return (1);
	light.intensity = dcolor_coef_multi(rgb, ratio);
	world->light = light;
	return (0);
}

int	parse_sphere(t_world *world, char **per_word_pointer)
{
	t_object	*sphere;
	t_dcolor	color;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 4)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	sphere = malloc(sizeof(t_object));
	if (sphere == NULL)
		return (1);
	sphere->identifier = SPHERE;
	if (set_vector(&sphere->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (1);
	sphere->diameter = ft_atod(per_word_pointer[2]);
	if (sphere->diameter < 0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[2]), 1);
	if (set_rgb(&color, per_word_pointer[3]) != 0)
		return (1);
	sphere->material = init_material(color,
		dcolor_init(SPECULAR_COEFFICIENT, SPECULAR_COEFFICIENT, SPECULAR_COEFFICIENT), SHININESS,
		dcolor_init(1, 1, 1));
	//if (sphere->material.use_perfect_reflectance == true)
	//	printf("true\n");
	return (add_object_to_lst(world, sphere));
}

int	parse_plane(t_world *world, char **per_word_pointer)
{
	t_object	*plane;
	t_dcolor		color;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 4)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	plane = malloc(sizeof(t_object));
	if (plane == NULL)
		return (1);
	plane->identifier = PLANE;
	if (set_vector(&plane->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (1);
	if (set_vector(&plane->orientation_vec, per_word_pointer[2], -1, 1) != 0)
		return (1);
	if (normalize_checker(&plane->orientation_vec, per_word_pointer[2]) != 0)
		return (1);
	if (set_rgb(&color, per_word_pointer[3]) != 0)
		return (1);
	plane->material = init_material(color,
		dcolor_init(SPECULAR_COEFFICIENT, SPECULAR_COEFFICIENT, SPECULAR_COEFFICIENT), SHININESS,
		dcolor_init(0, 0, 0));
	return (add_object_to_lst(world, plane));
}

int	parse_cylinder(t_world *world, char **per_word_pointer)
{
	t_object	*cylinder;
	t_dcolor		color;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 6)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	cylinder = malloc(sizeof(t_object));
	if (cylinder == NULL)
		return (1);
	cylinder->identifier = CYLINDER;
	if (set_vector(&cylinder->coordinates_vec, per_word_pointer[1], 0, 0) != 0)
		return (1);
	if (set_vector(&cylinder->orientation_vec, per_word_pointer[2], -1, 1) != 0)
		return (1);
	if (normalize_checker(&cylinder->orientation_vec, per_word_pointer[2]) != 0)
		return (1);
	cylinder->diameter = ft_atod(per_word_pointer[3]);
	if (cylinder->diameter < 0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[3]), 1);
	cylinder->height = ft_atod(per_word_pointer[4]);
	if (cylinder->height < 0)
		return (print_err_msg(OUT_OF_RANGE, per_word_pointer[4]), 1);
	if (set_rgb(&color, per_word_pointer[5]) != 0)
		return (1);
	cylinder->material = init_material(color,
		dcolor_init(SPECULAR_COEFFICIENT, SPECULAR_COEFFICIENT, SPECULAR_COEFFICIENT), SHININESS,
		dcolor_init(0, 0, 0));
	return (add_object_to_lst(world, cylinder));
}

int	parse_triangle(t_world *world, char **per_word_pointer)
{
	t_object	*triangle;
	t_dcolor		color;
	t_vector	center;

	if (per_word_pointer == NULL)
		return (1);
	if (ft_double_pointer_size(per_word_pointer) != 5)
		return (print_err_msg(NOT_MATCH_PARAM_NUM, per_word_pointer[0]), 1);
	triangle = malloc(sizeof(t_object));
	if (triangle == NULL)
		return (1);
	triangle->identifier = TRIANGLE;
	if (set_vector(&triangle->vertex.v1, per_word_pointer[1], 0, 0) != 0)
		return (1);
	if (set_vector(&triangle->vertex.v2, per_word_pointer[2], 0, 0) != 0)
		return (1);
	if (set_vector(&triangle->vertex.v3, per_word_pointer[3], 0, 0) != 0)
		return (1);
	center = calculate_center(triangle->vertex.v1, triangle->vertex.v2, triangle->vertex.v3);
	triangle->coordinates_vec = center;
	if (set_rgb(&color, per_word_pointer[4]) != 0)
		return (1);
	triangle->material = init_material(color,
		dcolor_init(SPECULAR_COEFFICIENT, SPECULAR_COEFFICIENT, SPECULAR_COEFFICIENT), SHININESS,
		dcolor_init(0, 0, 0));
	printf("parse triangle\n");
	return (add_object_to_lst(world, triangle));
}
