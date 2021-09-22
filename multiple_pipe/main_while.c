/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 10:36:06 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/20 10:16:36 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int *get_pipes(int nb_pipes)
{
    int i;
    int *pipes;

    i = -1;
    pipes = malloc(sizeof(int) * nb_pipes * 2);
    while (++i < nb_pipes)
    {
        pipe(pipes + i * 2);
    }
    return (pipes);
}

void    my_dup(int index, int *pipes, int nb_commands)
{
    //  FOR THE COMMAND 1 : DUP2(pipes[1], STDOUT);
    //                      Close all pipes_fds;
    //                      Execve;

    //  FOR THE COMMAND 2 : DUP2(pipes[0], STDIN);
    //                      DUP2(pipes[3], STDOUT);
    //                      Close all pipes_fds; Execve;

    //  FOR THE COMMAND 3 : DUP2(pipes[2], STDIN);
    //                      Close al pipes_fd; Execve
    if (index == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);

        close(pipes[0]);
        close(pipes[1]);
        close(pipes[2]);
        close(pipes[3]);
    }
    else if (index == nb_commands - 1)
    {
        dup2(pipes[2], STDIN_FILENO);
    
        close(pipes[0]);
        close(pipes[1]);
        close(pipes[2]);
        close(pipes[3]);
    }
    else
    {
        dup2(pipes[0], STDIN_FILENO);
        dup2(pipes[3], STDOUT_FILENO);        
    
        close(pipes[0]);
        close(pipes[1]);
        close(pipes[2]);
        close(pipes[3]);
    }
}

pid_t   *my_forks(char **cat, char **grep, char **cut, int *pipes, int nb_cmd)
{
    int     i;
    pid_t   *pids;

    i = -1;
    pids = malloc(sizeof(pid_t) * nb_cmd);
    while (++i < nb_cmd)
    {
        if ((pids[i] = fork()) == 0)
        {
            my_dup(i, pipes, nb_cmd);
            if (i == 0)
                execvp(*cat, cat);
            if (i == 1)
                execvp(*grep, grep);
            if (i == 2)
                execvp(*cut, cut);
        }
    }
    return (pids);
}

int main()
{
    int     i;
    int     wstatus;
    int     *pipes;
    pid_t   *pids;

    char *cat_args[] = {"ls", "..", "-la", NULL};
    char *grep_args[] = {"grep", "dr", NULL};
    char *cut_args[] = {"cat", NULL};

    pipes = get_pipes(2);

    pids = my_forks(cat_args, grep_args, cut_args, pipes, 3);
    
    close(pipes[0]);
    close(pipes[1]);
    close(pipes[2]);
    close(pipes[3]);

    for (i = 0; i < 3; i++)
    {
        // wait(&status);
        waitpid(pids[i], &wstatus, 0);
        printf("status %d : %d | %d\n", i, pids[i], wstatus);
    }
    return (0);
}