/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:59:02 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/18 19:19:55 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*init_pipes(int nb)
{
	int		i;
	int		ret;
	int		tmp;
	int		*pipes;

	i = -1;
	pipes = malloc(sizeof(int) * (nb - 1) * 2);
	while (++i < nb)
	{
		printf("c\n");
		ret = pipe(pipes + 2 * i);
		if (ret == -1)
			ft_error("pipe", 1);
	}
	// int		j = -1;
	// printf("BEF :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	// while (++j < (nb - 1) * 2)
	// {
		// printf("fd : [%d]\n", pipes[j]);
	// }
	// printf("AFT :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	int j = -1;
	while (++j < (nb - 1))
	{
		printf("c\n");
		tmp = pipes[j * 2];
		pipes[j * 2] = pipes[j * 2 + 1];
		pipes[j * 2 + 1] = tmp;
	}
	// j = -1;
	// while (++j < (nb - 1) * 2)
	// {
	// 	printf("fd : [%d]\n", pipes[j]);
	// }
	return (pipes);
}
int g_fd;

void	child_process(int index, t_execution *execution, int *pipes)
{
	int		i;
	int		ret_execve;
	
	i = -1;

	if (index == 0 && execution[0].nb_pipelines > 1)		//	First
	{
		// printf("last :: [%d\n", index - 1);
		dup2(pipes[0], STDOUT);
	}
	else if (index == execution[0].nb_pipelines - 1)	//	Last
	{
		printf("last :: [%d\n", index);
			dup2(pipes[index], STDIN);
	}
	else	// Middle
	{
		printf("middle :: [%d], [%d]\n", index, index + 1);
		dup2(pipes[index * 2 - 1], STDIN);
		dup2(pipes[index * 2], STDOUT);
	}
	i = -1;
	while (++i < (execution[0].nb_pipelines - 1) * 2)
	{		// if (!(i == fds_index[0] || i == fds_index[1]))
		printf("child closed fd : %d\n", i);
			close(pipes[i]);
	}
	ret_execve = execve(execution[index].exec_path, execution[index].args, g_env.env);
	printf("RET EXECVE : [%d] %sFATAAAAAAAAAAAAL A ZOOOBI%s\n", ret_execve, KRED, KWHT);
	printf("ERRROR D ZEEB : %s\n", strerror(errno));
}

void	create_childs(t_execution *execution, int *pipes)
{
	int		i;
	// int		status;
	int		*status;
	pid_t	pid;

	i = -1;
	status = malloc(sizeof(int) * execution[0].nb_pipelines);
	while (++i < execution[0].nb_pipelines)
	{
		printf("%sFOOOOOORK\n", KGRN);
		pid = fork();
		if (pid == 0)
		{
			child_process(i, execution, pipes);
		}
		close(pipes[i * 2]);
		// close(pipes[i]);
	}
	i = -1;
	waitpid(-1, &status[i], 0);
	while (++i < (execution[0].nb_pipelines - 1) * 2)
	{	// if (!(i == fds_index[0] || i == fds_index[1]))
		printf("parent closed fd : %d\n", i);
			close(pipes[i]);
	}// i = -1;
	// while (++i < execution[0].nb_pipelines)
		// wait(&status);
}

t_execution	*execute_line(t_execution *execution)
{
	int		i;
	int		*pipes;

	i = -1;
	pipes = init_pipes(execution[0].nb_pipelines);
	create_childs(execution, pipes);


	printf("%sEND OF EXECUTION\n", KYEL);

	return (execution);
}