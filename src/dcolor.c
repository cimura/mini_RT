/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcolor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:47 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/08 18:32:00 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dcolor.h"

t_dcolor	dcolor_coef_multi(t_dcolor rgb, double coefficient)
{
	t_dcolor	color;

	color.red = rgb.red * coefficient;
	color.green = rgb.green * coefficient;
	color.blue = rgb.blue * coefficient;
	return (color);
}

t_dcolor	dcolor_init(double red, double green, double blue)
{
	t_dcolor	color;

	color.red = red;
	color.green = green;
	color.blue = blue;
	return (color);
}

t_dcolor	dcolor_add(t_dcolor l1, t_dcolor l2)
{
	t_dcolor	result;

	result.red = l1.red + l2.red;
	if (result.red > 1.0)
		result.red = 1.0;
	result.green = l1.green + l2.green;
	if (result.green > 1.0)
		result.green = 1.0;
	result.blue = l1.blue + l2.blue;
	if (result.blue > 1.0)
		result.blue = 1.0;
	return (result);
}

t_dcolor	dcolor_multi(t_dcolor l1, t_dcolor l2)
{
	t_dcolor	result;

	result.red = l1.red * l2.red;
	result.green = l1.green * l2.green;
	result.blue = l1.blue * l2.blue;
	return (result);
}

// 赤は上位16ビット 緑は中間8ビット 青は下位8ビット
int	rgb_to_colorcode(t_dcolor light)
{
	int	result;

	result = (int)(light.red * 255) << 16
		| (int)(light.green * 255) << 8
		| (int)(light.blue * 255);
	return (result);
}
