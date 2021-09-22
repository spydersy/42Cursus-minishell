/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:59:02 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/22 12:17:33 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int *init_pipes(int nb_pipes)
{
    int     i;
    int     *pipes;
    
    i = -1;
    pipes = malloc(sizeof(int) * 2 * nb_pipes);
    while (++i < nb_pipes)
    {
        pipe(pipes + i * 2);
    }
    return (pipes);
}

void    close_all_fds(int *pipes, int nb_pipes)
{
    int     i;

    i = -1;
    while (++i < nb_pipes * 2)
    {
        close(pipes[i]);
    }
}

void    child_process(int index, int *pipes, t_execution *execution)
{
    int     ret;
    
    if (index == 0) //  FIRST
    {
        printf("%sFIRST\n%s", KYEL, KWHT);
        dup2(pipes[index * 2 + 1], STDOUT);
    }
    else if (index == execution[0].nb_pipelines - 1) // LAST
    {
        printf("%sLAST\n%s", KYEL, KWHT);
        dup2(pipes[index * 2 - 2], STDIN);
        // dup2(pipes[index * 2 + 1], STDOUT);
    }
    else    // MIDDLE
    {
        printf("%sMIDDLE\n%s", KYEL, KWHT);
        dup2(pipes[index * 2 - 2], STDIN);
        dup2(pipes[index * 2 + 1], STDOUT);
    }
    close_all_fds(pipes, execution[0].nb_pipelines - 1);
    ret = execve(execution[index].exec_path, execution[index].args, g_env.env);
    printf("ERROR EXECVE : %d\n", ret);
}

void   create_childs(t_execution *execution)
{
    int     i;
    int     *pipes;
    pid_t   pid;
    int     status;
    
    i = -1;
    pipes = init_pipes(execution[0].nb_pipelines - 1);
    while (++i < execution[0].nb_pipelines)
    {
        pid = fork();
        if (pid == 0)
        {
            child_process(i, pipes, execution);
        }
    }
    close_all_fds(pipes, execution[0].nb_pipelines - 1);
    waitpid(-1, &status, 0);
}

t_execution	*execute_line(t_execution *execution)
{

    create_childs(execution);
    printf("%sEND OF EXECUTION%s\n", KYEL, KWHT);
	return (execution);
}