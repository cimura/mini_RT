#ifndef FT_MLX_H
# define FT_MLX_H

#include "draw.h"
#include "mlx.h"

typedef struct s_imge
{
	void	*ptr;
	char	*pixel_ptr;
	int		bpp;
	int		endian;
	int		line_length;
}				t_imge;

typedef struct s_mlx
{
	void	*ptr;
	void	*win_ptr;
	t_imge	*img;
}	t_mlx;

void	my_pixel_put(int x, int y, t_imge *img, int color);
void	init(t_mlx *mlx);

#endif