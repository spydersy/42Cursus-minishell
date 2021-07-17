/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execution2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 12:40:43 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/16 20:03:16 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    redirections_handler(int index, t_tokens *tokens)
{
    int     i;
    int     c;
    int     *infile;
    int     *outfile;

    c = 0;
    i = -1;
    while (tokens[index].type[++i] < tokens[index].nb)
    {
        if ()
        {
            
        }
    }
}

void    child_process(t_tokens *tokens, int *pipes)
{
    int     i;
    pid_t   pid;

    i = -1;
    while (++i < tokens->pipe)
    {
        pid  = fork();
        if (pid == -1)
            ft_error("FORK", 1);
        if (pid == 0) //child process
        {
            //  child_process
            //  redirectoin priority (IO) is for files redirections not pipes;
            //  About INPUT FILE  :  IF infile exist we must duplicate STDIN WITH FILE_FD
            //                       ELSE we must duplicate STDIN WITH PIPE_IN
            //  About OUTPUT FILE :  IF outfile exist we must create it & duplicate STDOUT WITH FILE_FD
            //                       ELSE we must duplicate STDOUT WITH PIPE_OUT
            redirections_handler(i, tokens);
        }
    }
    // while (++i < (tokens->pipe - 1) * 2)
    // {
        // printf("PIPES FD : %d\n", pipes[i]);
    // }
}

int     to_execution2(t_tokens *tokens)
{
    int     i;
    int     pipes[(tokens->pipe - 1) * 2];

    i = -1;
    if (tokens->pipe == 1)
    {
        //exe_one_command();
    }
    else
    {
        while (++i < tokens->pipe - 1)
        {
            if (pipe(pipes + 2 * i) == -1)
                ft_error("PIPES", 1);
        }
        child_process(tokens, pipes);
    }

    return (0);
}