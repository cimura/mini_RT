/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:26:23 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/21 16:42:11 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H

# define OBJECT_H

# include "vector.h"
# include "dcolor.h"
# include "texture.h"
# include "libft.h"

enum	e_material
{
	GLASS,
	IRON,
	SILVER,
	WOOD,
	WATER,
};

typedef struct s_material
{
	t_dcolor	diffuse;
	t_dcolor	specular;
	double		shinness;
	bool		use_perfect_reflectance;
	t_dcolor	catadioptric_factor;
	bool		use_refraction;
	double		refractive_index;
	bool		use_thin_surfase;
}	t_material;

// オブジェクト汎用
typedef struct s_object
{
	int				identifier;
	t_vector3		coordinates_vec;
	t_vector3		orientation_vec;
	double			diameter;
	double			height;
	t_list			*textures;
	t_material		material;
}	t_object;


// *** material.c ***
int			material_register(char **per_word_pointer, t_material *material,
	int obj_identifier);

// *** object.c ***
t_object	*object_init(void);
void		object_destroy(void *pointer);

// *** texture_register.c ***
int			texture_register(char **filenames, t_list **lst);
t_texture	*init_new_texture(char *filename);

#endif