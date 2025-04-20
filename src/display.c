/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:17:04 by ttakino           #+#    #+#             */
/*   Updated: 2025/04/20 15:45:06 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	handle_win_input(t_world *world)
{
	on_destroy(world);
	return (0);
}

static int	key_press(int keysym, t_world *world)
{
	if (keysym == ESC_KEY)
		on_destroy(world);
	return (0);
}

void	display_in_mlx(t_world *world)
{
	mlx_put_image_to_window(world->mlx.ptr,
		world->mlx.win_ptr, world->mlx.img->ptr, 0, 0);
	mlx_hook(world->mlx.win_ptr, 2, 1L << 0, key_press, world);
	mlx_hook(world->mlx.win_ptr, 17, 0, handle_win_input, world);
	mlx_loop(world->mlx.ptr);
}
