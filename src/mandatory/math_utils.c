/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 06:31:37 by paulo             #+#    #+#             */
/*   Updated: 2024/02/26 06:31:48 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
