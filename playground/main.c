#include "mlx.h"
#include "mlx_int.h"

#define	WIDTH 1000
#define	HEIGHT 1000

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

void	close_handler(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img->ptr);
	mlx_destroy_window(mlx->ptr, mlx->win_ptr);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape)
		close_handler(mlx);
	return (0);
}

int	main() {
	t_mlx	mlx;
	init(&mlx);

	mlx_key_hook(mlx.win_ptr, key_handler, &mlx);
	
		// printf("i is %d\n", i);
		// my_pixel_put(&mlx, mlx.win_ptr, HEIGHT/2, i, 0xFF0000);
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if ((x - WIDTH/2)*(x - WIDTH/2) + (y - HEIGHT/2)*(y - HEIGHT/2) <= 10000)
				my_pixel_put(x, y, mlx.img, (0xFF0000 + x*2)/255);
			else
				my_pixel_put(x, y, mlx.img, 0x30FF00);
		}
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->ptr, 0, 0);
	mlx_loop(mlx.ptr);
}
