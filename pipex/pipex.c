/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 10:10:16 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/24 07:14:16 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getPath(char *cmd, char **envp)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	while (path && ft_strnchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strnchr(path, ':'));
		bin = join_path(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strnchr(path, ':') + 1;
	}
	return (cmd);
}

int	openfile(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
		{
			write(STDERR, "pipex: ", 7);
			write(STDERR, filename, ft_strnchr(filename, 0));
			write(STDERR, ": No such file or directory\n", 28);
			return (STDIN);
		}
		return (open(filename, O_RDONLY));
	}
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

void	exec(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (ft_strnchr(args[0], '/') > -1)
		path = args[0];
	else
		path = getPath(args[0], envp);
	execve(path, args, envp);
	write(STDERR, "pipex: ", 7);
	if (ft_strncmp(cmd, "", 2) == 0)
	{
		write(STDERR, "permission denied: \n", 20);
		exit(126);
	}
	write(STDERR, "command not found: ", 19);
	write(STDERR, path, ft_strnchr(path, '\0'));
	write(STDERR, "\n", 1);
	exit(127);
}

void	redir(char *cmd, char **envp, int fd, int *status)
{
	pid_t	pid;
	int		pipes[2];

	pipe(pipes);
	pid = fork();
	if (pid)
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN);
		waitpid(pid, status, 0);
	}
	else
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT);
		if (fd == STDIN)
			exit(1);
		else
			exec(cmd, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		status;

	data.pipenb = 2;
	data.ac = ac;
	data.av = av;
	data.status = &status;
	data.envp = envp;
	if (ac == 5)
	{
		data.infd = openfile(av[1], INFILE);
		data.outfd = openfile(av[4], OUTFILE);
		check_fds(data.infd, data.outfd, ac, av);
		dup2(data.infd, STDIN);
		dup2(data.outfd, STDOUT);
		redir(av[2], envp, data.infd, data.status);
		execute(&data);
	}
	else
	{
		write(STDERR, "Invalid number of arguments.\n", 29);
		return (1);
	}
	while (1);
	return (WEXITSTATUS(status));
}
