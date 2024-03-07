/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:35:58 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/03/07 19:03:01 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	toggle_door(t_cub3d *cub3d, int x, int y);

void	verify_door(t_cub3d *cub3d)
{
	if (cub3d->dir.y < 0 && fabs(cub3d->dir.y) > fabs(cub3d->dir.x))
		toggle_door(cub3d, 0, -1);
	if (cub3d->dir.y > 0 && fabs(cub3d->dir.y) > fabs(cub3d->dir.x))
		toggle_door(cub3d, 0, 1);
	if (cub3d->dir.x < 0 && fabs(cub3d->dir.x) > fabs(cub3d->dir.y))
		toggle_door(cub3d, -1, 0);
	if (cub3d->dir.x > 0 && fabs(cub3d->dir.x) > fabs(cub3d->dir.y))
		toggle_door(cub3d, 1, 0);
}

static void	toggle_door(t_cub3d *cub3d, int x, int y)
{
	int	player_x;
	int	player_y;

	player_x = (int)(cub3d->player.x);
	player_y = (int)(cub3d->player.y);
	if (cub3d->map[player_y + y][player_x + x] == '2')
		cub3d->map[player_y + y][player_x + x] = '3';
	else if (cub3d->map[player_y + y][player_x + x] == '3')
		cub3d->map[player_y + y][player_x + x] = '2';
}
