/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:07:16 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/01/29 22:27:45 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
