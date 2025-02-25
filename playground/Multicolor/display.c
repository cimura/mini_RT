/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:17:04 by ttakino           #+#    #+#             */
/*   Updated: 2025/02/25 14:17:05 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

// ×ボタンで閉じる
static int	handle_win_input(t_mlx *mlx)
{
	on_destroy(*mlx);
	return (0);
}

// escキーで閉じる
static int	key_press(int keysym, t_mlx *mlx)
{
	if (keysym == ESC_KEY)
		on_destroy(*mlx);
	return (0);
}

void	display_in_mlx(t_mlx mlx)
{
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->ptr, 0, 0);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, handle_win_input, &mlx);
	mlx_loop(mlx.ptr);
}
