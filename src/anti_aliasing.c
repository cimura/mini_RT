/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:18:14 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/09 19:13:02 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_dcolor	**frame_buffer_init(int width, int height)
{
	t_dcolor	**frame_buffer;
	int			i;

	frame_buffer = malloc(height * sizeof(t_dcolor *));
	if (frame_buffer == NULL)
		return (NULL);
	i = 0;
	while (i < height)
	{
		frame_buffer[i] = malloc(width * sizeof(t_dcolor));
		if (frame_buffer[i] == NULL)
			return (free_double_pointer((void **)frame_buffer), NULL);
		i++;
	}
	return (frame_buffer);
}

static void	add_pixel_color(t_dcolor pixel_color, t_dcolor *result, int *count)
{
	result->red = result->red + pixel_color.red;
	result->green = result->green + pixel_color.green;
	result->blue = result->blue + pixel_color.blue;
	(*count)++;
}

static bool	pixel_cmp(t_dcolor p1, t_dcolor p2)
{
	if ((p1.red - p2.red) + (p1.green - p2.green) + (p1.blue - p2.blue) > 0.2)
		return (true);
	return (false);
}

static t_dcolor	get_pixel_average_color(t_dcolor **frame_buffer,
	int x, int y)
{
	t_dcolor	result;
	int			count;

	result = frame_buffer[y][x];
	count = 1;
	if (x - 1 >= 0 && pixel_cmp(frame_buffer[y][x], frame_buffer[y][x - 1]))
		add_pixel_color(frame_buffer[y][x - 1], &result, &count);
	if (x + 1 < WIDTH && pixel_cmp(frame_buffer[y][x], frame_buffer[y][x + 1]))
		add_pixel_color(frame_buffer[y][x + 1], &result, &count);
	if (y - 1 >= 0 && pixel_cmp(frame_buffer[y][x], frame_buffer[y - 1][x]))
		add_pixel_color(frame_buffer[y - 1][x], &result, &count);
	if (y + 1 < HEIGHT && pixel_cmp(frame_buffer[y][x], frame_buffer[y + 1][x]))
		add_pixel_color(frame_buffer[y + 1][x], &result, &count);
	if (count > 2)
	{
		result.red = result.red / count;
		result.green = result.green / count;
		result.blue = result.blue / count;
		return (result);
	}
	return (frame_buffer[y][x]);
}

int	anti_aliasing(t_world *world)
{
	t_dcolor	**new_frame_buffer;
	int			y;
	int			x;

	new_frame_buffer = frame_buffer_init(WIDTH, HEIGHT);
	if (new_frame_buffer == NULL)
		return (1);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			new_frame_buffer[y][x]
				= get_pixel_average_color(world->frame_buffer, x, y);
			x++;
		}
		y++;
	}
	free_double_pointer((void **)world->frame_buffer);
	world->frame_buffer = new_frame_buffer;
	return (0);
}
