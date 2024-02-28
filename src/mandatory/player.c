/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:31:11 by paulo             #+#    #+#             */
/*   Updated: 2024/02/27 21:06:31 by bedos-sa         ###   ########.fr       */
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

void	move_player(t_cub3d *cub3d, double speed, int angle)
{
	double	x_speed;
	double	y_speed;

	if (angle == 0)
	{
		x_speed = cub3d->dir.x * speed;
		y_speed = cub3d->dir.y * speed;
	}
	else
	{
		x_speed = -cub3d->dir.y * speed * angle;
		y_speed = cub3d->dir.x * speed * angle;
	}
	if (cub3d->map[(int)(cub3d->player.y)][(int)(cub3d->player.x
			+ x_speed)] == '0')
		cub3d->player.x += x_speed;
	if (cub3d->map[(int)(cub3d->player.y
			+ y_speed)][(int)(cub3d->player.x)] == '0')
		cub3d->player.y += y_speed;
}
