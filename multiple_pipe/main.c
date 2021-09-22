/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 09:19:35 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/19 09:29:05 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    char    *cmd_and_args[] = {"vim", "somewhere", NULL};
    char    *cmd_paths = "/usr/bin/vim";


    int ret = execve(cmd_paths, cmd_and_args, envp);
    printf("ret : %d FATAL\n", ret);
    return (0);
}
