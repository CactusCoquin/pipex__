#include "pipex.h"

static char	*get_path_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static int	open_file(char *path_cmd)
{
	return (open(path_cmd, O_RDONLY));
}

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	get_path(char *cmd, char *envp[], char **f_path)
{
	char	**paths;
	char	*path;
	char	*path_cmd;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(get_path_env(envp), ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(path, cmd);
		fd = open_file(path_cmd);
		if (fd >= 0)
		{
			*f_path = path_cmd;
			free_paths(paths);
			close(fd);
			return ;
		}
		free(path_cmd);
		free(path);
		i++;
	}
	free_paths(paths);
}

char	**split_cmd_arg(char *argv)
{
	return (ft_split(argv, ' '));
}