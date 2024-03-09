/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:31:11 by paulo             #+#    #+#             */
/*   Updated: 2024/03/08 23:59:52 by paulo            ###   ########.fr       */
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

void	move_player(t_cub3d *cub3d, double speed, int signal)
{
	double	x_speed;
	double	y_speed;

	if (signal == 0)
	{
		x_speed = cub3d->dir.x * speed;
		y_speed = cub3d->dir.y * speed;
	}
	else
	{
		x_speed = -signal * cub3d->dir.y * speed;
		y_speed = signal * cub3d->dir.x * speed;
	}
	if ((cub3d->player.x + x_speed + get_signal(x_speed)) > WALL_OFFSET
		&& (cub3d->player.x + x_speed + get_signal(x_speed)) < (cub3d->map_x - 1
			- WALL_OFFSET))
		cub3d->player.x += x_speed;
	if ((cub3d->player.y + y_speed + get_signal(y_speed)) > WALL_OFFSET
		&& (cub3d->player.y + y_speed + get_signal(y_speed)) < (cub3d->map_y
			- WALL_OFFSET))
		cub3d->player.y += y_speed;
}
