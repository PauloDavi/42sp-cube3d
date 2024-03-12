/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 06:31:37 by paulo             #+#    #+#             */
/*   Updated: 2024/03/11 22:13:50 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	safe_ray_dist_calc(double ray)
{
	if (ray == 0)
		return (DBL_MAX);
	return (fabs(1 / ray));
}

int	get_signal(double num)
{
	if (num < 0)
		return (-1);
	return (1);
}

uint32_t	rgb_to_int(uint8_t *rgb)
{
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | rgb[3]);
}

double	distance(t_vector *pos1, t_vector *pos2)
{
	return ((pos1->x - pos2->x) * (pos1->x - pos2->x) + (pos1->y - pos2->y) \
		* (pos1->y - pos2->y));
}

void	sort_sprites(t_cub3d *cub3d, t_sprite **arr)
{
	bool	swapped;
	double	dist1;
	double	dist2;
	int		i;
	int		n;

	swapped = true;
	n = 0;
	while (arr[n] != NULL)
		n++;
	while (swapped)
	{
		swapped = false;
		i = -1;
		while (++i < n - 1)
		{
			dist1 = distance(&arr[i]->position, &cub3d->player);
			dist2 = distance(&arr[i + 1]->position, &cub3d->player);
			if (dist1 < dist2)
			{
				ft_pswap((void **)&arr[i], (void **)&arr[i + 1]);
				swapped = true;
			}
		}
	}
}
