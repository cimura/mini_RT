/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:59:01 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/22 18:46:50 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H

# define MINI_RT_H

# define DEBUG

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "vector.h"
# include "dcolor.h"
# include "object.h"
# include "texture.h"
# include "ft_mlx.h"
# include "utils.h"
# include "libft.h"

enum	e_obj_identifier
{
	ATOMOSPHERE = 3,
	AMBIENT_LIGHTNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
};

typedef struct s_ambient_lightning
{
	int			identifier;
	t_dcolor	intensity;
}	t_ambient_lightning;

typedef struct s_camera
{
	int			identifier;
	t_vector3	coordinates_vec;
	t_vector3	orientation_vec;
	int			horizontal_fov;
	t_vector3	x_basis;
	t_vector3	y_basis;
	t_vector3	center_of_screen;
}	t_camera;

typedef struct s_light
{
	int			identifier;
	t_vector3	coordinates_vec;
	t_dcolor	intensity;
}	t_light;

// 描画対象の図形（円、平面、円柱）は複数個扱えるように配列にする
typedef struct s_world
{
	t_mlx				mlx;
	t_texture			*skybox;
	double				global_refractive_index;
	t_ambient_lightning	ambient_lightning;
	t_camera			camera;
	t_list				*lights;
	t_list				*objects;
}	t_world;

//# include "renderer.h"

// *** diaplay.c ***
void		display_in_mlx(t_world *world);

// *** parser.c ***
int			parse_arguments(t_world *scene, int argc, char **argv);

// *** renderer.c ***
int			renderer(t_world *world);

// *** main.c ***
void		world_destroy(t_world *world);
void		on_destroy(t_world *world);

#endif
