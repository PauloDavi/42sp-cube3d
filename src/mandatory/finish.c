/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:31:25 by paulo             #+#    #+#             */
/*   Updated: 2024/01/27 11:31:32 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_for_finish(t_cube3d *cube3d)
{
	ft_free_split(cube3d->map);
	mlx_delete_image(cube3d->mlx_ptr, cube3d->image);
}
