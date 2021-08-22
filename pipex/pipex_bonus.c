/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 08:20:24 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/07/05 09:37:46 by ael-ghem         ###   ########.fr       */
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
	else if (mode == OUTFILE)
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	else
		return (open(filename, O_CREAT | O_WRONLY | O_APPEND,
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
	if (ac < 5 && write(STDERR, "Invalid number of arguments.\n", 29))
		return (1);
	if ((ft_strncmp(av[1], "here_doc", 8) == 0) && data.pipenb++)
	{
		data.infd = openfile(here_doc("/tmp/heredoc420", av), INFILE);
		data.outfd = openfile(av[ac - 1], APPFILE);
	}
	else
	{
		data.infd = openfile(av[1], INFILE);
		data.outfd = openfile(av[ac - 1], OUTFILE);
	}
	check_fds(data.infd, data.outfd, ac, av);
	dup2(data.infd, STDIN);
	dup2(data.outfd, STDOUT);
	execute(&data);
	return (WEXITSTATUS(data.status));
}
