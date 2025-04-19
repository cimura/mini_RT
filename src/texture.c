/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:12:17 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/19 17:54:34 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fcntl.h>

int	load_texture(t_texture *tex, char *filename, int identifier)
{
	tex->identifier = identifier;
	tex->data = NULL;
	tex->data
		= stbi_load(filename, &tex->width, &tex->height, &tex->channels, 0);
	if (tex->data == NULL)
		return (1);
	printf("width: %d height: %d cannels: %d\n", tex->width, tex->height, tex->channels);
	return (0);
}

t_vector3	texture_get_normal(t_texture *tex, int x, int y)
{
	t_vector3		normal_vec;
	int				index;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	index = (y * tex->width + x) * tex->channels;
	r = tex->data[index];
	g = tex->data[index + 1];
	b = tex->data[index + 2];
	normal_vec.x = (r / 255.0) * 2.0 - 1.0;
	normal_vec.y = (g / 255.0) * 2.0 - 1.0;
	normal_vec.z = (b / 255.0) * 2.0 - 1.0;
	return (normal_vec);
}

t_dcolor	texture_get_color(t_texture *tex, int x, int y)
{
	t_dcolor		color;
	int				index;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	index = (y * tex->width + x) * tex->channels;
	r = tex->data[index];
	g = tex->data[index + 1];
	b = tex->data[index + 2];
	color.red = (r / 255.0);
	color.green = (g / 255.0);
	color.blue = (b / 255.0);
	return (color);
}

void	texture_free(void *pointer)
{
	t_texture	*tex;

	if (pointer == NULL)
		return ;
	tex = (t_texture *)pointer;
	if (tex->data)
		stbi_image_free(tex->data);
	free(pointer);
}
