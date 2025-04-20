/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:59:41 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 16:34:20 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	object_free(void *pointer)
{
	t_object	*object;

	object = (t_object *)pointer;
	ft_lstclear(&object->textures, texture_free);
	free(pointer);
}

void	world_destroy(t_world *world)
{
	texture_free((void *)world->skybox);
	ft_lstclear(&world->lights, free);
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
	world_destroy(world);
	exit(0);
}

int	init_world(t_world *world)
{
	world->skybox = NULL;
	world->ambient_lightning.identifier = 0;
	world->camera.identifier = 0;
	world->lights = NULL;
	world->objects = NULL;
	return (0);
}

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
	if (renderer(&world) != 0)
		return (on_destroy(&world), 1);
	display_in_mlx(&world);
}
