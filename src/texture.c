/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:12:17 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/10 00:06:45 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "vector.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int	load_texture(t_texture *tex, char *filename)
{
	tex->data
		= stbi_load(filename, &tex->width, &tex->height, &tex->channels, 0);
	printf("width: %d height:%d channels:%d\n", tex->width, tex->height, tex->channels);
	if (tex->data == NULL)
		return (1);
	return (0);
}

t_vector	texture_get_normal(t_texture *tex, int x, int y)
{
	t_vector		normal_vec;
	int				index;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	index = (y * tex->width + x) * tex->channels;
	if (tex->data[index])
		r = tex->data[index];
	if (tex->data[index + 1])
		g = tex->data[index + 1];
	if (tex->data[index + 2])
		b = tex->data[index + 2];
	normal_vec.x = (r / 255.0) * 2.0 - 1.0;
	normal_vec.y = (g / 255.0) * 2.0 - 1.0;
	normal_vec.z = (b / 255.0) * 2.0 - 1.0;
	return (normal_vec);
}

void	texture_free(t_texture *tex)
{
	stbi_image_free(tex->data);
}
