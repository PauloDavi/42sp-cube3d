/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:49:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/07 19:14:18 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static bool	is_empty_line(char *str)
{
	return (valid_charset(str, " \n") == NULL);
}

int	check_chars_map(int fd, char *str)
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
		printf("foi norte\n");
		return (1);
	}
	else if (!ft_strncmp(arr[0], SOUTH, 3))
	{
		printf("foi sul\n");
		return (1);
	}
	else if (!ft_strncmp(arr[0], WEST, 3))
	{
		printf("foi oeste\n");
		return (1);
	}
	else if (!ft_strncmp(arr[0], EAST, 3))
	{
		printf("foi leste\n");
		return (1);
	}
	else if (!ft_strncmp(arr[0], FLOOR, 2))
	{
		printf("foi chao\n");
		return (1);
	}
	else if (!ft_strncmp(arr[0], CEILING, 2))
	{
		printf("foi teto\n");
		return (1);
	}
	else
	{
		printf("foi nenhum\n");
		return (0);
	}
}

size_t	parse_parameters(t_cube3d *cube3d, int fd)
{
	char	*line;
	size_t	read_lines;
	int		num;
	(void)	cube3d;

	num = 0;
	read_lines = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		read_lines++;
		if (!is_empty_line(line))
			num += check_chars_map(fd, line);
		free(line);
		if (num == 6)
			break ;
	}
	return (read_lines);
}

// pular os espaços vazios que vem antes do mapa
// lidar com repetição de lihas
