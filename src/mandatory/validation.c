/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:07:16 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/01/30 20:39:38 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*valid_charset(char *str, char *set);
static int	valid_player(char *line);

char	*valid_args(int argc, char **argv)
{
	size_t	filename_size;
	size_t	extension_size;

	if (argc != 2)
		err_exit("Error\nInvalid number of arguments\n");
	filename_size = ft_strlen(argv[1]);
	extension_size = ft_strlen(FILE_EXTENSION);
	if (filename_size < extension_size)
		err_exit("Error\nInvalid filename\n");
	while (extension_size--)
	{
		if (argv[1][--filename_size] != FILE_EXTENSION[extension_size])
			err_exit("Error\nInvalid filename\n");
	}
	return (argv[1]);
}

void	valid_map(t_cube3d *cube3d)
{
	size_t	i;
	size_t	player_count;
	char	*invalid_char;

	i = 0;
	player_count = 0;
	while (i < cube3d->map_y)
	{
		invalid_char = valid_charset(cube3d->map[i], VALID_CHAR_SET);
		if (invalid_char != NULL)
		{
			ft_free_split(cube3d->map);
			ft_fprintf(STDERR_FILENO, ERR_INVALID_CHAR, *invalid_char);
			exit(EXIT_FAILURE);
		}
		get_player_position(cube3d, cube3d->map[i], i);
		player_count += valid_player(cube3d->map[i++]);
	}
	if (player_count != 1)
	{
		ft_fprintf(STDERR_FILENO, ERR_INVALID_PLAYER, player_count);
		ft_free_split(cube3d->map);
		exit(EXIT_FAILURE);
	}
}

static char	*valid_charset(char *str, char *set)
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

static int	valid_player(char *line)
{
	int index;
	int num;

	num = 0;
	while (*line != '\0')
	{
		index = 0;
		while (VALID_CHAR_SET_PLAYER[index] != '\0')
		{
			if (*line == VALID_CHAR_SET_PLAYER[index])
			{
				num++;
				break ;
			}
			index++;
		}
		line++;
	}
	return (num);
}