/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderozie <sderozie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:17:17 by sderozie          #+#    #+#             */
/*   Updated: 2023/05/05 18:19:09 by sderozie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(char *path, char **arg_cmd, char **envp)
{
	if (path)
	{
		if (execve(path, arg_cmd, envp) == -1)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(arg_cmd[0], 2);
			free_matrix(arg_cmd);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(arg_cmd[0], 2);
		free_matrix(arg_cmd);
		exit(EXIT_FAILURE);
	}
}

static void	first_child_process(int *fd, char **argv, char **envp)
{
	int		infile;
	char	*path;
	char	**arg_cmd;

	close(fd[FD_READ_END]);
	infile = open (argv[1], O_RDONLY);
	if (infile == -1)
	{
		ft_putendl_fd("Error infile", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(infile, STDIN_FILENO) == -1
		|| dup2(fd[FD_WRITE_END], STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("Error dup2 1st process", 2);
		exit(EXIT_FAILURE);
	}
	close(infile);
	close(fd[FD_WRITE_END]);
	arg_cmd = ft_split(argv[2], ' ');
	if (access(arg_cmd[0], X_OK) == 0)
		path = ft_strdup(arg_cmd[0]);
	else
		get_path(arg_cmd[0], envp, &path);
	exec_cmd(path, arg_cmd, envp);
}

static	void	second_child_process(int *fd, char **argv, char **envp)
{
	int		outfile;
	char	*path;
	char	**arg_cmd;

	close(fd[FD_WRITE_END]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	if (outfile == -1)
	{
		ft_putendl_fd("Error outfile", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[FD_READ_END], STDIN_FILENO) == -1
		|| dup2(outfile, STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("Error dup2 2nd process", 2);
		exit(EXIT_FAILURE);
	}
	close(fd[FD_READ_END]);
	close(outfile);
	arg_cmd = ft_split(argv[3], ' ');
	if (access(arg_cmd[0], X_OK) == 0)
		path = ft_strdup(arg_cmd[0]);
	else
		get_path(arg_cmd[0], envp, &path);
	exec_cmd(path, arg_cmd, envp);
}

static void	pipex(pid_t *pid, int *fd, char **argv, char **envp)
{
	*pid = fork();
	if (*pid == -1)
	{
		ft_putendl_fd("Error fork", 1);
		exit(EXIT_FAILURE);
	}
	if (*pid == 0)
		first_child_process(fd, argv, envp);
	else
	{
		*pid = fork();
		if (*pid == -1)
		{
			ft_putendl_fd("Error 2nd fork", 2);
			exit(EXIT_FAILURE);
		}
		if (*pid == 0)
			second_child_process(fd, argv, envp);
		else
		{
			close(fd[FD_READ_END]);
			close(fd[FD_WRITE_END]);
		}
	}
	waitpid(*pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (!check_args(argc, argv))
	{
		ft_putendl_fd("Error in arguments", 1);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		ft_putendl_fd("Error pipe", 1);
		exit(EXIT_FAILURE);
	}
	pipex(&pid, fd, argv, envp);
	return (0);
}
