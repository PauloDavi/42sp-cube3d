/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 06:31:37 by paulo             #+#    #+#             */
/*   Updated: 2024/03/07 23:57:52 by paulo            ###   ########.fr       */
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
