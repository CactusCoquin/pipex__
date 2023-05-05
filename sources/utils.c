/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderozie <sderozie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:17:25 by sderozie          #+#    #+#             */
/*   Updated: 2023/05/05 18:07:36 by sderozie         ###   ########.fr       */
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

bool	check_args(int argc, char **argv)
{
	int	i;
	int	i2;

	if (argc != 5)
		return (false);
	i = 2;
	while (i < 4)
	{
		i2 = 0;
		while (argv[i][i2])
		{
			if (argv[i][i2] != ' ' && argv[i][i2] != '\t')
				return (true);
			i2++;
		}
		i++;
	}
	return (false);
}
