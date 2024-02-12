/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:07:16 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/12 13:22:53 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	valid_open_wall(t_cube3d *cube3d, size_t x, size_t y);

void	valid_walls(t_cube3d *cube3d)
{
	size_t	x;
	size_t	y;

	if (valid_charset(cube3d->map[0], "1 \n") != NULL
		|| valid_charset(cube3d->map[cube3d->map_y - 1], "1 \n") != NULL)
	{
		ft_free_split(cube3d->map);
		err_exit(ERR_INVALID_OPEN_MAP);
	}
	y = 1;
	while (y < (cube3d->map_y - 1))
	{
		x = 0;
		while (cube3d->map[y][x] != '\0' && cube3d->map[y][x] != '\n')
		{
			valid_open_wall(cube3d, x, y);
			x++;
		}
		y++;
	}
}

char	*valid_args(int argc, char **argv)
{
	size_t	filename_size;
	size_t	extension_size;

	if (argc != 2)
		err_exit(ERR_INVALID_ARG_NUM);
	filename_size = ft_strlen(argv[1]);
	extension_size = ft_strlen(FILE_EXTENSION);
	if (filename_size < extension_size)
		err_exit(ERR_INVALID_FILE_NAME);
	while (extension_size--)
	{
		if (argv[1][--filename_size] != FILE_EXTENSION[extension_size])
			err_exit(ERR_INVALID_FILE_NAME);
	}
	return (argv[1]);
}

void	valid_map(t_cube3d *cube3d)
{
	size_t	y;
	size_t	player_count;
	char	*invalid_char;

	y = 0;
	player_count = 0;
	while (y < cube3d->map_y)
	{
		invalid_char = valid_charset(cube3d->map[y], VALID_CHAR_SET);
		if (invalid_char != NULL)
		{
			ft_free_split(cube3d->map);
			ft_fprintf(STDERR_FILENO, ERR_INVALID_CHAR, *invalid_char);
			exit(EXIT_FAILURE);
		}
		player_count += valid_player(cube3d->map[y++]);
	}
	if (player_count != 1)
	{
		ft_fprintf(STDERR_FILENO, ERR_INVALID_PLAYER, player_count);
		ft_free_split(cube3d->map);
		exit(EXIT_FAILURE);
	}
	valid_walls(cube3d);
}

char	*valid_charset(char *str, char *set)
{
	size_t	index;

	while (*str != '\0')
	{
		index = 0;
		while (set[index] != '\0')
		{
			if (set[index] == *str)
				break ;
			index++;
		}
		if (set[index] == '\0')
			break ;
		str++;
	}
	if (*str == '\0')
		return (NULL);
	return (str);
}

static void	valid_open_wall(t_cube3d *cube3d, size_t x, size_t y)
{
	if (cube3d->map[y][x] != '1' && cube3d->map[y][x] != ' ')
	{
		if (x == 0 || cube3d->map[y][x + 1] == '\n' || cube3d->map[y][x
			+ 1] == '\0')
		{
			ft_free_split(cube3d->map);
			err_exit(ERR_INVALID_OPEN_MAP);
		}
		if (cube3d->map[y + 1][x] == ' ' || cube3d->map[y - 1][x] == ' '
			|| cube3d->map[y][x + 1] == ' ' || cube3d->map[y][x - 1] == ' ')
		{
			ft_free_split(cube3d->map);
			err_exit(ERR_INVALID_OPEN_MAP);
		}
	}
}
