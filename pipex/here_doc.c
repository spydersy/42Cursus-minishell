/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:35:39 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/07/01 08:32:36 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(t_data *data)
{
	pid_t	pid;
	int		pipes[2];

	while (data->pipenb < data->ac - 2)
		redir(data->av[data->pipenb++],
			data->envp, data->infd, data->status);
	pipe(pipes);
	pid = fork();
	if (pid)
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN);
		waitpid(pid, data->status, 0);
	}
	else
	{
		close(pipes[0]);
		dup2(pipes[1], data->outfd);
		exec(data->av[data->ac - 2], data->envp);
	}
}

void	check_fds(int infd, int outfd, int ac, char **av)
{
	if (infd < 0)
	{
		write(STDERR, "pipex: ", 7);
		write(STDERR, av[1], ft_strnchr(av[1], '\0'));
		write(STDERR, ": Permission denied", 19);
		write(STDERR, "\n", 1);
		exit(1);
	}
	if (outfd < 0)
	{
		write(STDERR, "pipex: ", 7);
		write(STDERR, av[ac - 1], ft_strnchr(av[ac - 1], '\0'));
		write(STDERR, ": Permission denied", 19);
		write(STDERR, "\n", 1);
		exit(1);
	}
}

char	*here_doc(char *path, char **av)
{
	int		infd;
	char	*buf;
	int		r;

	r = 42;
	buf = malloc(1025);
	infd = openfile(path, OUTFILE);
	while (r)
	{
		write(1, "heredoc> ", 9);
		r = read(0, buf, 1024);
		buf[r] = '\0';
		if ((ft_strncmp(buf, av[2], ft_strnchr(av[2], '\0')) == 0)
			&& (ft_strnchr(av[2], '\0') == ft_strnchr(buf, '\0') - 1))
			break ;
		if (ft_strnchr(buf, '\n') != -1)
			write(infd, buf, ft_strnchr(buf, '\n') + 1);
	}
	close(infd);
	free(buf);
	return (path);
}
