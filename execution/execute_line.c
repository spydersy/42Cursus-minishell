/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:59:02 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/18 17:28:27 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*init_pipes(int nb)
{
	int		i;
	int		ret;
	int		*pipes;

	i = -1;
	pipes = malloc(sizeof(int) * nb * 2);
	while (++i < nb)
	{
		ret = pipe(pipes + 2 * i);
		if (ret == -1)
			ft_error("pipe", 1);
	}
	return (pipes);
}

void	child_process(int index, t_execution *execution, int *pipes)
{
	int		i;
	int		fds_index[2];
	int		ret_execve;
	
	i = -1;
	fds_index[0] = index * 2; 
	fds_index[1] = index * 2 + 1; 
	if (index != execution[0].nb_pipelines  -1)
		dup2(pipes[fds_index[0]], STDIN);
	if (index != 0)
		dup2(pipes[fds_index[1]], STDOUT);
	while (++i < execution[0].nb_pipelines * 2)
		if (!(i == fds_index[0] || i == fds_index[1]))
			close(pipes[i]);
	ret_execve = execve(execution[index].exec_path, execution[index].args, g_env.env);
	printf("RET EXECVE : [%d] %sFATAAAAAAAAAAAAL A ZOOOBI%s\n", ret_execve, KRED, KWHT);
	printf("ERRROR D ZEEB : %s\n", strerror(errno));
}

void	create_childs(t_execution *execution, int *pipes)
{
	int		i;
	int		status;
	
	i = -1;
	while (++i < execution[0].nb_pipelines)
	{
		if (fork() == 0)
		{
			child_process(i, execution, pipes);
		}
	}
	i = -1;
	while (++i < execution[0].nb_pipelines)
		wait(&status);
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