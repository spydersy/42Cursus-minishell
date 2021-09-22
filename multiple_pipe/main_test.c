/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 10:03:11 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/19 10:47:24 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/**
 * Executes the command "cat scores | grep Villanova | cut -b 1-10".
 * This quick-and-dirty version does no error checking.
 *
 * @author Jim Glenn
 * @version 0.1 10/4/2004
 */

int main(int argc, char **argv)
{
    int status;
    int i;

    char *cat_args[] = {"cat", "scores", NULL};
    char *grep_args[] = {"grep", "Villanova", NULL};
    char *cut_args[] = {"cut", "-b", "1-10", NULL};


    int pipes[4];
    pipe(pipes); // sets up 1st pipe
    pipe(pipes + 2); // sets up 2nd pipe
    //MY GET_PIPES;

    if (fork() == 0)
    {
        dup2(pipes[1], 1);


        close(pipes[0]);
        close(pipes[1]);
        close(pipes[2]);
        close(pipes[3]);

        execvp(*cat_args, cat_args);
    }
    else
    {

    if (fork() == 0)
	{

	    dup2(pipes[0], 0);


	  dup2(pipes[3], 1);


	  close(pipes[0]);
	  close(pipes[1]);
	  close(pipes[2]);
	  close(pipes[3]);

	  execvp(*grep_args, grep_args);
	}
      else
	{

	  if (fork() == 0)
	    {

	      dup2(pipes[2], 0);


	    close(pipes[0]);
	    close(pipes[1]);
	    close(pipes[2]);
	    close(pipes[3]);

	    execvp(*cut_args, cut_args);
	    }
	}
    }


    close(pipes[0]);
    close(pipes[1]);
    close(pipes[2]);
    close(pipes[3]);

  for (i = 0; i < 3; i++)
    wait(&status);
}
