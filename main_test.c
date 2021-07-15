/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 12:15:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 12:20:28 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int             ret;
    struct stat     statbuf;

    ret = stat("main.c", &statbuf);
    printf("%u\n", statbuf.st_mode);
    printf("ret : %d\n", ret);
    return (0);
}