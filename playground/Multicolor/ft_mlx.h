/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:16:57 by ttakino           #+#    #+#             */
/*   Updated: 2025/03/15 18:37:59 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include "draw.h"
# include "mlx.h"

# define ESC_KEY 65307

typedef struct s_imge
{
	void	*ptr;
	char	*pixel_ptr;
	int		bpp;
	int		endian;
	int		line_length;
}	t_imge;

typedef struct s_mlx
{
	void	*ptr;
	void	*win_ptr;
	t_imge	*img;
}	t_mlx;

// *** ft_mlx.c ***
void	my_pixel_put(int x, int y, t_imge *img, int color);
int		init_mlx(t_mlx *mlx);

#endif