#include "pipex.h"

static int	setup_fd(char *file, int flags, mode_t mode)
{
	int	fd;

	fd = open(file, flags, mode);
	check_fd(fd, file);
	return (fd);
}

static char	**setup_cmd_args(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = split_cmd_arg(cmd);
	if (access(args[0], X_OK) == 0)
		path = ft_strdup(args[0]);
	else
		get_path(args[0], envp, &path);
	args[0] = path;
	return (args);
}

static void	execute_cmd(char **args)
{
	if (execve(args[0], args, NULL) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		free_matrix(args);
		exit(0);
	}
}

static void	child_process(int *fd, char **argv, char **envp, int in_fd, int out_fd)
{
	close(fd[FD_READ_END]);
	dup2(in_fd, STDIN_FILENO);
	close(fd[FD_WRITE_END]);
	dup2(out_fd, STDOUT_FILENO);
	execute_cmd(setup_cmd_args(argv[2], envp));
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		fd[2];

	check_argv(argc);
	pipe(fd);
	pid = fork();
	if (pid == -1)
		perror("Error");
	if (pid == 0)
		child_process(fd, argv, envp, setup_fd(argv[1], O_RDONLY, 0), fd[FD_WRITE_END]);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (pid == 0)
			child_process(fd, argv, envp, fd[FD_READ_END], setup_fd(argv[4], O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU));
		else
		{
			close(fd[FD_READ_END]);
			close(fd[FD_WRITE_END]);
		}
	}
	waitpid(pid, NULL, 0);
	return (0);
}