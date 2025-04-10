/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:12:17 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/10 23:29:05 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//t_texture	*texture_init(int identifier)
//{
//	t_texture	*tex;

//	tex->data = NULL;
//	tex->width = 0;
//	tex->height = 0;
//	tex->channels = 0;
//}

int	load_texture(t_texture *tex, char *filename, int identifier)
{
	tex->identifier = identifier;
	tex->data
		= stbi_load(filename, &tex->width, &tex->height, &tex->channels, 0);
	printf("width: %d height:%d channels:%d\n", tex->width, tex->height, tex->channels);
	if (tex->data == NULL)
		return (1);
	return (0);
}

int	texture_register(char *filename, t_list **lst)
{
	t_texture	*tex;
	int			identifier;
	t_list		*node;

	tex = malloc(sizeof(t_texture));
	if (tex == NULL)
		return (1);
	// TODO identifierを決める処理
	identifier = NORMAL;

	if (load_texture(tex, filename, identifier) != 0)
		return (free(tex), 1);
	node = ft_lstnew(tex);
	if (node == NULL)
		return (free(tex), 1);
	ft_lstadd_front(lst, node);
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

void	texture_free(void *pointer)
{
	t_texture	*tex;

	tex = (t_texture *)pointer;
	stbi_image_free(tex->data);
	free(pointer);
}
