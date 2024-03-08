/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:31:25 by paulo             #+#    #+#             */
/*   Updated: 2024/03/07 23:57:52 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_texture(t_cub3d *cub3d)
{
	if (cub3d->south_texture != NULL)
		mlx_delete_texture(cub3d->south_texture);
	if (cub3d->north_texture != NULL)
		mlx_delete_texture(cub3d->north_texture);
	if (cub3d->west_texture != NULL)
		mlx_delete_texture(cub3d->west_texture);
	if (cub3d->east_texture != NULL)
		mlx_delete_texture(cub3d->east_texture);
}

void	free_for_finish(t_cub3d *cub3d)
{
	free_texture(cub3d);
	ft_free_split(cub3d->map);
	mlx_delete_image(cub3d->mlx_ptr, cub3d->image);
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

void	close_free_err_exit(int fd, char **arr, char *err_message)
{
	ft_free_split(arr);
	close_err_exit(fd, err_message);
}
