/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:59:41 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/10 00:12:27 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	object_free(void *pointer)
{
	t_object	*object;

	object = (t_object *)pointer;
	texture_free(&object->normal_tex);
	free(pointer);
}

void	free_objects(t_world *world)
{
	free_double_pointer((void **)world->frame_buffer);
	ft_lstclear(&world->lights, object_free);
	ft_lstclear(&world->objects, object_free);
}

void	on_destroy(t_world *world)
{
	if (world->mlx.img && world->mlx.img->ptr)
		mlx_destroy_image(world->mlx.ptr, world->mlx.img->ptr);
	if (world->mlx.win_ptr)
		mlx_destroy_window(world->mlx.ptr, world->mlx.win_ptr);
	if (world->mlx.ptr)
	{
		mlx_destroy_display(world->mlx.ptr);
		free(world->mlx.ptr);
	}
	free_objects(world);
	exit(0);
}

int	init_world(t_world *world)
{
	world->frame_buffer = frame_buffer_init(WIDTH, HEIGHT);
	if (world->frame_buffer == NULL)
		return (1);
	world->ambient_lightning.identifier = 0;
	world->camera.identifier = 0;
	world->lights = NULL;
	world->objects = NULL;
	return (0);
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

	if (init_world(&world) != 0)
		return (1);
	if (parse_arguments(&world, argc, argv) != 0)
		return (1);
	world.global_refractive_index = 1.000293;
	if (init_mlx_struct(&world.mlx) != 0)
		return (on_destroy(&world), 1);
	#ifdef DEBUG
	long	start = get_current_time();
	#endif
	printf("rendering...\n");
	if (renderer(&world) != 0)
		return (on_destroy(&world), 1);
	printf("100%%\n");
	#ifdef DEBUG
	long	end = get_current_time();
	printf("rendering: %ldms\n", end - start);
	#endif
	display_in_mlx(&world);
}
