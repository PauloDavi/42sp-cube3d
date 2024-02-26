/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:31:11 by paulo             #+#    #+#             */
/*   Updated: 2024/02/26 06:44:55 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_player(char *line)
{
	int	index;
	int	num;

	num = 0;
	while (*line != '\0')
	{
		index = 0;
		while (VALID_CHAR_SET_PLAYER[index] != '\0')
		{
			if (*line == VALID_CHAR_SET_PLAYER[index])
			{
				num++;
				break ;
			}
			index++;
		}
		line++;
	}
	return (num);
}

void	rotate_player(t_cub3d *cub3d, double angle)
{
	double	old_x;

	old_x = cub3d->dir.x;
	cub3d->dir.x = cub3d->dir.x * cos(angle) - cub3d->dir.y * sin(angle);
	cub3d->dir.y = old_x * sin(angle) + cub3d->dir.y * cos(angle);
	old_x = cub3d->plane.x;
	cub3d->plane.x = cub3d->plane.x * cos(angle) - cub3d->plane.y * sin(angle);
	cub3d->plane.y = old_x * sin(angle) + cub3d->plane.y * cos(angle);
}

void	move_player(t_cub3d *cub3d, double speed)
{
	double	x_speed;
	double	y_speed;

	x_speed = cub3d->dir.x * speed;
	y_speed = cub3d->dir.y * speed;
	if (cub3d->map[(int)(cub3d->player.y)][(int)(cub3d->player.x
			+ x_speed)] == '0')
		cub3d->player.x += x_speed;
	if (cub3d->map[(int)(cub3d->player.y
			+ y_speed)][(int)(cub3d->player.x)] == '0')
		cub3d->player.y += y_speed;
}

void	draw_player(t_cub3d *cub3d)
{
	t_vector	map_point;
	t_vector	dir_point;
	t_vector	plane_point;

	map_point.x = cub3d->player.x * MINI_MAP_TILE_SIZE;
	map_point.y = cub3d->player.y * MINI_MAP_TILE_SIZE;
	dir_point.x = (cub3d->player.x + cub3d->dir.x) * MINI_MAP_TILE_SIZE;
	dir_point.y = (cub3d->player.y + cub3d->dir.y) * MINI_MAP_TILE_SIZE;
	plane_point.x = (cub3d->player.x + cub3d->dir.x + cub3d->plane.x)
		* MINI_MAP_TILE_SIZE;
	plane_point.y = (cub3d->player.y + cub3d->dir.y + cub3d->plane.y)
		* MINI_MAP_TILE_SIZE;
	draw_line(cub3d, &dir_point, &plane_point, PLAYER_COLOR);
	plane_point.x = (cub3d->player.x + cub3d->dir.x - cub3d->plane.x)
		* MINI_MAP_TILE_SIZE;
	plane_point.y = (cub3d->player.y + cub3d->dir.y - cub3d->plane.y)
		* MINI_MAP_TILE_SIZE;
	draw_line(cub3d, &dir_point, &plane_point, PLAYER_COLOR);
	draw_line(cub3d, &map_point, &dir_point, PLAYER_COLOR);
	draw_circle(cub3d, &map_point, MINI_MAP_TILE_SIZE / 5, PLAYER_COLOR);
}
