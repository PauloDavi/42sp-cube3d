/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:49:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/08 20:24:21 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static bool	is_empty_line(char *str)
{
	return (valid_charset(str, " \n") == NULL);
}

static void	check_chars_map(t_cube3d* cube3d, int fd, char *str)
{
	char	**arr;
	size_t	size;

	arr = ft_split_size(str, ' ', &size);
	if (size != 2)
	{
		ft_free_split(arr);
		close_err_exit(fd, "Error\nInvalid parameter\n");
	}
	if (!ft_strncmp(arr[0], NORTH, 3))
	{
		printf("%s\n", arr[1]);
		cube3d->north_texture = mlx_load_png(arr[1]);
		if (cube3d->north_texture == NULL)
        {
			ft_free_split(arr);
			close_err_exit(fd, "Error\nInvalid map texture\n");
		}
	}
	else if (!ft_strncmp(arr[0], SOUTH, 3))
	{
		cube3d->south_texture = mlx_load_png(arr[1]);
		if (cube3d->north_texture == NULL)
        {
			ft_free_split(arr);
			close_err_exit(fd, "Error\nInvalid map texture\n");
		}
	}
	else if (!ft_strncmp(arr[0], WEST, 3))
	{
		cube3d->west_texture = mlx_load_png(arr[1]);
		if (cube3d->north_texture == NULL)
        {
			ft_free_split(arr);
			close_err_exit(fd, "Error\nInvalid map texture\n");
		}
	}
	else if (!ft_strncmp(arr[0], EAST, 3))
	{
		cube3d->east_texture = mlx_load_png(arr[1]);
		if (cube3d->north_texture == NULL)
        {
			ft_free_split(arr);
			close_err_exit(fd, "Error\nInvalid map texture\n");
		}
	}
	else if (!ft_strncmp(arr[0], FLOOR, 2))
	{
		cube3d->floor_color = 0;
	}
	else if (!ft_strncmp(arr[0], CEILING, 2))
	{
		cube3d->ceiling_color = 0;
	}
	else
	{
		ft_free_split(arr);
		close_err_exit(fd, "Error\nInvalid map texture or map color name\n");
	}
}

size_t	parse_parameters(t_cube3d *cube3d, int fd)
{
	char	*line;
	size_t	read_lines;
	int		num;

	num = 0;
	read_lines = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		read_lines++;
		line = remove_new_line(line);
		if (!is_empty_line(line))
			check_chars_map(cube3d, fd, line);
		free(line);
		if (cube3d->south_texture != NULL && cube3d->south_texture != NULL && \
			cube3d->west_texture != NULL && cube3d->east_texture != NULL && \
			cube3d->ceiling_color != -1 && cube3d->floor_color != -1)
			break ;
	}
	return (read_lines);
}
