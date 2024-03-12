/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:31:25 by paulo             #+#    #+#             */
/*   Updated: 2024/03/11 19:46:21 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	invalid_parameter_exit(t_cub3d *cub3d, int fd, char **words,
		char *str)
{
	free_gnl_memory(fd);
	free_texture(cub3d);
	close_free_err_exit(fd, words, str);
}

void	free_map_and_texture(t_cub3d *cub3d)
{
	ft_free_split(cub3d->map);
	free_texture(cub3d);
	exit(EXIT_FAILURE);
}
