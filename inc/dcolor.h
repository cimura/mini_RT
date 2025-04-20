/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcolor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:30:22 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 14:14:37 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCOLOR_H

# define DCOLOR_H

// RGB 計算しやすく0.0~1.0の範囲で表す
typedef struct s_color
{
	double	red;
	double	green;
	double	blue;
}	t_dcolor;

// *** dcolor.c ***
t_dcolor		dcolor_coef_multi(t_dcolor rgb, double coefficient);
t_dcolor		dcolor_init(double red, double green, double blue);
t_dcolor		dcolor_add(t_dcolor l1, t_dcolor l2);
t_dcolor		dcolor_multi(t_dcolor l1, t_dcolor l2);
int				rgb_to_colorcode(t_dcolor light);

#endif