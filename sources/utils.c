/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderozie <sderozie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:08:47 by byanis            #+#    #+#             */
/*   Updated: 2023/05/04 12:50:51 by sderozie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	check_argv(int argc)
{
	if (argc != 5)
	{
		printf("Arg: ./pipex infile command1 command2 outfile\n");
		exit(0);
	}
}

void	check_fd(int fd, char *file)
{
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(file, 2);
		exit(0);
	}
}
