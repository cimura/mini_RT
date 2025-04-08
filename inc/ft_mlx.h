/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:00:58 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/08 20:16:19 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"

# define WIDTH	512
# define HEIGHT	512

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

void	my_pixel_put(int x, int y, t_imge *img, int color);
int		init_mlx_struct(t_mlx *mlx);

#endif