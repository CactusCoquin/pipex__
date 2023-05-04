/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderozie <sderozie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:08:54 by byanis            #+#    #+#             */
/*   Updated: 2023/05/04 12:54:31 by sderozie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void	get_path(char *cmd, char *envp[], char **f_path)
{
	char	**paths;
	char	*path;
	char	*path_cmd;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(ft_strchr(find_path(envp), '/'), ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(path, cmd);
		free(path);
		fd = open(path_cmd, O_RDONLY);
		if (fd >= 0)
		{
			*f_path = path_cmd;
			free_matrix(paths);
			close(fd);
			return ;
		}
		free(path_cmd);
		i++;
	}
	free_matrix(paths);
}
