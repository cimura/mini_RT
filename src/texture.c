/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:12:17 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/16 21:24:55 by sshimura         ###   ########.fr       */
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
 #include <fcntl.h>
int	load_texture(t_texture *tex, char *filename, int identifier)
{
	int		fd;
	char	buf[25];
	char	**per_line;
	int		i;
	int		j;
	int		tex_i;

	fd = open("debug.ber", O_RDONLY);
	if (fd < 0)
	{
		printf("open failed\n");
		return (1);
	}
	read(fd, buf, 24);
	buf[24] = '\0';
	printf("buf:%s\n", buf);
	per_line = ft_split(buf, '\n');
	if (per_line == NULL)
	{
		printf("perline failed\n");
		return (1);
	}
	tex->data = malloc((20 * 3) * sizeof(unsigned char));
	if (tex->data == NULL)
	{
		printf("tex->data failed\n");
		return (1);
	}
	tex_i = 0;
	i = 0;
	while (per_line[i] != NULL)
	{
		j = 0;
		while (per_line[i][j])
		{
			if (per_line[i][j] == 1)
			{
				tex->data[tex_i] = 255;
				tex->data[tex_i + 1] = 0;
				tex->data[tex_i + 2] = 0;
			}
			else if (per_line[i][j] == 2)
			{
				tex->data[tex_i] = 0;
				tex->data[tex_i + 1] = 255;
				tex->data[tex_i + 2] = 0;
			}
			else if (per_line[i][j] == 3)
			{
				tex->data[tex_i] = 0;
				tex->data[tex_i + 1] = 0;
				tex->data[tex_i + 2] = 255;
			}
			else
			{
				tex->data[tex_i] = 0;
				tex->data[tex_i + 1] = 0;
				tex->data[tex_i + 2] = 0;
			}
			tex_i += 3;
			j++;
		}
		i++;
	}
	// DEBUG
	tex->identifier = identifier;
	(void)filename;
	//tex->data = malloc((4*5) * sizeof(unsigned char));
	//tex->data = (unsigned char *){0,0,0,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,0};
	tex->channels = 3;
	tex->height = j - 1;
	tex->width = ft_strlen(per_line[0]);
	tex->fase_side_len = tex->height / 4;
	printf("tex:\nwidth %d\nheight %d\nchannels %d\nfasesidelen %d\n", tex->width, tex->height, tex->channels, tex->fase_side_len);
	free(per_line);
	return (0);

	//tex->identifier = identifier;
	//tex->data
	//	= stbi_load(filename, &tex->width, &tex->height, &tex->channels, 0);
	//printf("width: %d height:%d channels:%d\n", tex->width, tex->height, tex->channels);
	////tex->size = sizeof(tex->data);
	//tex->fase_side_len = tex->height / 4;
	//printf("fase_side_len: %d\n", tex->fase_side_len);
	//if (tex->data == NULL)
	//	return (1);
	//return (0);
}

int	texture_register(char **filename, t_list **lst)
{
	t_texture	*tex;
	int			identifier;
	t_list		*node;
	int			i;

	i = 0;
	while (filename[i] != NULL)
	{
		tex = malloc(sizeof(t_texture));
		if (tex == NULL)
			return (1);
		// TODO identifierを決める処理
		// if (ft_strncmp(filename[i], "tex/Rock051_1K-PNG_NormalGL.png", 28) == 0)
		else if (ft_strncmp(filename[i], "earth_normal.png", 25) == 0)
			identifier = NORMAL;
		// else if (ft_strncmp(filename[i], "tex/Rock051_1K-PNG_Color.png", 25) == 0)
		else if (ft_strncmp(filename[i], "earth_color_map.png", 25) == 0)
			identifier = COLOR;
	
		if (load_texture(tex, filename[i], identifier) != 0)
			return (free(tex), 1);
		node = ft_lstnew(tex);
		if (node == NULL)
			return (free(tex), 1);
		ft_lstadd_front(lst, node);
		i++;
	}
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
	//if (index < tex->size)
		r = tex->data[index];
	//if (index + 1 < tex->size)
		g = tex->data[index + 1];
	//if (index + 2 < tex->size)
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
	//if (index < tex->size)
		r = tex->data[index];
	//if (index + 1 < tex->size)
		g = tex->data[index + 1];
	//if (index + 2 < tex->size)
		b = tex->data[index + 2];
	color.red = (r / 255.0);
	color.green = (g / 255.0);
	color.blue = (b / 255.0);
	return (color);
}

void	texture_free(void *pointer)
{
	t_texture	*tex;

	tex = (t_texture *)pointer;
	stbi_image_free(tex->data);
	free(pointer);
}
