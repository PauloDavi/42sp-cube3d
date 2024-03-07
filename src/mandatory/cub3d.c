/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:43:10 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/19 22:32:22 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(void *param)
{
	t_cub3d	*cub3d;
	int		x_pos;
	int		y_pos;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_M))
	{
		draw_wallpaper(cub3d, 0x000000FF, 0x000000FF);
		draw_mini_map(cub3d);
	}
	else
	{
		draw_wallpaper(cub3d, cub3d->floor_color, cub3d->ceiling_color);
		distance_rays(cub3d);
	}
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx_ptr);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_W))
		move_player(cub3d, PLAYER_SPEED, 0);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_S))
		move_player(cub3d, -PLAYER_SPEED, 0);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_A))
		move_player(cub3d, -PLAYER_SPEED, 1);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_D))
		move_player(cub3d, -PLAYER_SPEED, -1);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_RIGHT))
		rotate_player(cub3d, PLAYER_ROTATE_SPEED);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_LEFT))
		rotate_player(cub3d, -PLAYER_ROTATE_SPEED);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_SPACE))
		verify_door(cub3d);
	mlx_get_mouse_pos(cub3d->mlx_ptr, &x_pos, &y_pos);
	if (x_pos > cub3d->mouse.x)
		rotate_player(cub3d, PLAYER_ROTATE_SPEED);
	if (x_pos < cub3d->mouse.x)
		rotate_player(cub3d, -PLAYER_ROTATE_SPEED);
	cub3d->mouse.x = x_pos;
	cub3d->mouse.y = y_pos;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	start_params(&cub3d);
	read_map(&cub3d, valid_args(argc, argv));
	normalize_map(&cub3d);
	valid_map(&cub3d);
	initialize(&cub3d);
	mlx_set_cursor_mode(cub3d.mlx_ptr, MLX_MOUSE_DISABLED);
	mlx_loop_hook(cub3d.mlx_ptr, ft_hook, &cub3d);
	mlx_loop(cub3d.mlx_ptr);
	free_for_finish(&cub3d);
	mlx_terminate(cub3d.mlx_ptr);
	return (EXIT_SUCCESS);
}
