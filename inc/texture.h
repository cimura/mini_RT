/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:40:41 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/22 21:47:18 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H

# define TEXTURE_H

# include "libft.h"
# include "vector.h"
# include "dcolor.h"
# include <stdbool.h>
# include <fcntl.h>

# define STB_IMAGE_IMPLEMENTATION
# define TEX_MAGNIFICATION 0.01

enum	e_tex_identifier
{
	SKYBOX,
	NORMAL,
	COLOR,
	NONE,
};

typedef struct s_uv
{
	int	u;
	int	v;
}	t_uv;

typedef struct s_texture
{
	int				identifier;
	unsigned char	*data;
	int				width;
	int				height;
	int				channels;
}	t_texture;

// *** texture.c ***
int			load_texture(t_texture *tex, char *filename, int identifier);
t_vector3	texture_get_normal(t_texture *tex, int x, int y);
t_dcolor	texture_get_color(t_texture *tex, int x, int y);
void		texture_destroy(void *pointer);

#endif