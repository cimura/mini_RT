/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:40:41 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/09 23:49:27 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H

# define TEXTURE_H

# include "vector.h"

typedef struct s_texture
{
	unsigned char	*data;
	int				width;
	int				height;
	int				channels;
}	t_texture;

// *** texture.c ***
int			load_texture(t_texture *tex, char *filename);
t_vector	texture_get_normal(t_texture *tex, int x, int y);
void		texture_free(t_texture *tex);

#endif