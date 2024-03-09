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

#include "cub3d_bonus.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_SPACE)
		verify_door(cub3d);
}

void	main_hook(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	draw_wallpaper(cub3d, cub3d->floor_color, cub3d->ceiling_color);
	distance_rays(cub3d);
	draw_mini_map(cub3d);
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
}

void	mouse_hook(double x_pos, double y_pos, void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
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
	mlx_loop_hook(cub3d.mlx_ptr, main_hook, &cub3d);
	mlx_cursor_hook(cub3d.mlx_ptr, &mouse_hook, &cub3d);
	mlx_key_hook(cub3d.mlx_ptr, key_hook, &cub3d);
	mlx_loop(cub3d.mlx_ptr);
	free_for_finish(&cub3d);
	mlx_terminate(cub3d.mlx_ptr);
	return (EXIT_SUCCESS);
}
