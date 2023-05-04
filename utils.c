#include "pipex.h"

void	check_argv(int argc)
{
	if (argc != 5)
	{
		printf("Arg: ./pipex infile comand1 comand2 outfile\n");
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
