/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:59:41 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/05 22:11:40 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// プログラムを終了するときに呼ぶ mlx関係のポインタをfreeする mlx以外をfreeするようにしてもいいかも
void	on_destroy(t_world world)
{
	if (world.mlx.img && world.mlx.img->ptr)
		mlx_destroy_image(world.mlx.ptr, world.mlx.img->ptr);
	if (world.mlx.win_ptr)
		mlx_destroy_window(world.mlx.ptr, world.mlx.win_ptr);
	if (world.mlx.ptr)
	{
		mlx_destroy_display(world.mlx.ptr);
		free(world.mlx.ptr);
	}
	ft_lstclear(&world.lights, NULL);
	ft_lstclear(&world.objects, NULL);
	exit(0);
}

#ifdef DEBUG
#include <sys/time.h>
long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
#endif

int	main(int argc, char **argv)
{
	t_world	world;

	if (parse_arguments(&world, argc, argv) != 0)
		return (1);
	world.global_refractive_index = 1.000293;
	if (init_mlx_struct(&world.mlx) != 0)
		return (1);
	#ifdef DEBUG
		long	start = get_current_time();
	#endif
	printf("rendering...\n");
	render_scene(&world);
	printf("100%%\n");
	#ifdef DEBUG
		long	end = get_current_time();
		printf("rendering: %ldms\n", end - start);
	#endif
	display_in_mlx(world);
}
