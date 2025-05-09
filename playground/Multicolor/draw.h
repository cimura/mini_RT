/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:17:07 by ttakino           #+#    #+#             */
/*   Updated: 2025/02/25 14:37:47 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define	WIDTH	512
#define	HEIGHT	512

#define	R	1
#define	ALPHA	8
/*
	環境光反射係数
		𝑘𝑎=0.01
	拡散反射係数
		𝑘𝑑=0.69
	鏡面反射係数
		𝑘𝑠=0.3
	光沢度
		𝛼=8
	環境光の強度
		𝐼𝑎=0.1
	光源の光の強度
		𝐼𝑖=1.0
*/
typedef struct s_const
{
	double	k_a;
	double	k_d;
	double	k_s;
	double	I_a;
	double	I_i;
}	t_const;

typedef struct s_color
{
	double	value;
	double	R_r;
	t_const	constant;
}	t_color;

#include "vector.h"

typedef struct s_sphere_draw
{
	t_color		color;
	t_vector	center;
	double		radius;
}	t_sphere_draw;

__int32_t	map(t_color red, t_color green, t_color blue);

#endif