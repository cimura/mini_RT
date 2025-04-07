/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:58:59 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/07 23:23:57 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

void	my_pixel_put(int x, int y, t_imge *img, int color)
{
	int	offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = (y * img->line_length) + (x * (img->bpp / 8));
		*(unsigned int *)(img->pixel_ptr + offset) = color;
	}
}

static int	init_img(t_mlx *mlx)
{
	mlx->img = malloc(sizeof(t_imge));
	if (mlx->img == NULL)
		return (1);
	mlx->img->ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (mlx->img->ptr == NULL)
	{
		free(mlx->img);
		return (1);
	}
	mlx->img->pixel_ptr = mlx_get_data_addr(mlx->img->ptr, &mlx->img->bpp,
			&mlx->img->line_length, &mlx->img->endian);
	return (0);
}

int	init_mlx_struct(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win_ptr
		= mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "miniRT");
	if (init_img(mlx) != 0)
		return (1);
	return (0);
}
