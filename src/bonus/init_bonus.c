/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:24:46 by paulo             #+#    #+#             */
/*   Updated: 2024/03/10 12:04:46 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_mini_image(t_cub3d *cub3d);

void	initialize(t_cub3d *cub3d)
{
	int	x_pos;
	int	y_pos;

	cub3d->mlx_ptr = mlx_init(WIDTH, HEIGHT, GAME_NAME, false);
	if (cub3d->mlx_ptr == NULL)
		exit(EXIT_FAILURE);
	cub3d->image = mlx_new_image(cub3d->mlx_ptr, WIDTH, HEIGHT);
	if (cub3d->image == NULL)
	{
		mlx_close_window(cub3d->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub3d->mlx_ptr, cub3d->image, 0, 0) == -1)
	{
		mlx_delete_image(cub3d->mlx_ptr, cub3d->image);
		mlx_close_window(cub3d->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	init_mini_image(cub3d);
	mlx_get_mouse_pos(cub3d->mlx_ptr, &x_pos, &y_pos);
	cub3d->mouse.x = y_pos;
	cub3d->mouse.y = y_pos;
}

static void	init_mini_image(t_cub3d *cub3d)
{
	cub3d->mini_image = mlx_new_image(cub3d->mlx_ptr, MINI_MAP_WIDTH,
			MINI_MAP_HEIGHT);
	if (cub3d->mini_image == NULL)
	{
		mlx_delete_image(cub3d->mlx_ptr, cub3d->image);
		mlx_close_window(cub3d->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub3d->mlx_ptr, cub3d->mini_image, 10, 10) == -1)
	{
		mlx_delete_image(cub3d->mlx_ptr, cub3d->image);
		mlx_delete_image(cub3d->mlx_ptr, cub3d->mini_image);
		mlx_close_window(cub3d->mlx_ptr);
		exit(EXIT_FAILURE);
	}
}

void	start_params(t_cub3d *cub3d)
{
	cub3d->dir.x = 0;
	cub3d->dir.y = -1;
	cub3d->plane.x = 0.66;
	cub3d->plane.y = 0;
	cub3d->west_texture = NULL;
	cub3d->north_texture = NULL;
	cub3d->east_texture = NULL;
	cub3d->south_texture = NULL;
	cub3d->door_texture = NULL;
	cub3d->wall_door_texture = NULL;
	cub3d->sprite_texture = NULL;
	cub3d->sprites_list = NULL;
	cub3d->floor_color = -1;
	cub3d->ceiling_color = -1;
}
