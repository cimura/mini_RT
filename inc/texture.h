/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:40:41 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/11 23:20:24 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H

# define TEXTURE_H

# include "libft.h"
# include "vector.h"
# include "dcolor.h"
# include <stdbool.h>

enum	e_tex_identifier
{
	NORMAL,
	COLOR,
};

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
int			texture_register(char **filename, t_list **lst);
t_vector	texture_get_normal(t_texture *tex, int x, int y);
t_dcolor	texture_get_color(t_texture *tex, int x, int y);
void		texture_free(void *pointer);

#endif