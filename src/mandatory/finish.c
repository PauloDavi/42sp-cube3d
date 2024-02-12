/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:31:25 by paulo             #+#    #+#             */
/*   Updated: 2024/02/12 13:46:59 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_texture(t_cube3d *cube3d)
{
	if (cube3d->south_texture != NULL)
		mlx_delete_texture(cube3d->south_texture);
	if (cube3d->north_texture != NULL)
		mlx_delete_texture(cube3d->north_texture);
	if (cube3d->west_texture != NULL)
		mlx_delete_texture(cube3d->west_texture);
	if (cube3d->east_texture != NULL)
		mlx_delete_texture(cube3d->east_texture);
}

void	free_for_finish(t_cube3d *cube3d)
{
	free_texture(cube3d);
	ft_free_split(cube3d->map);
	mlx_delete_image(cube3d->mlx_ptr, cube3d->image);
}

void	err_exit(char *str)
{
	ft_fprintf(STDERR_FILENO, str);
	exit(EXIT_FAILURE);
}

void	close_err_exit(int fd, char *str)
{
	close(fd);
	ft_fprintf(STDERR_FILENO, str);
	exit(EXIT_FAILURE);
}

void	close_free_err_exit(int fd, char **arr, char *err_mesage)
{
	ft_free_split(arr);
	close_err_exit(fd, err_mesage);
}
