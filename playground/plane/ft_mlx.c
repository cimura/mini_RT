#include "ft_mlx.h"

void	my_pixel_put(int x, int y, t_imge *img, int color)
{
	// printf("img ptr: %p\n", img);
	// printf("pixel ptr: %p\n", img->pixel_ptr);
	// printf("pixel value: %d\n", *img->pixel_ptr);
	int	offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = (y * img->line_length) + (x * (img->bpp / 8));
		*(unsigned int *)(img->pixel_ptr + offset) = color;
	}
}

void	init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->img = malloc(sizeof(t_imge));
	mlx->win_ptr = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "WINDOW");
	mlx->img->ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (mlx->img->ptr == NULL)
		perror("img");
	mlx->img->pixel_ptr = mlx_get_data_addr(mlx->img->ptr, &mlx->img->bpp, &mlx->img->line_length, &mlx->img->endian);
}