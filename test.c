/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:11:37 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/18 17:12:39 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

// int	main()
// {
// 	char *arr[] = { "Makefile", NULL};
// 	char *path = "/bin/cat";

// 	int ret = execve(path, arr, NULL);
// 	printf("%d", ret);
// 	return (0);
// }

int	main()
{
	int fd;
	char	*buffer;

	fd = open("main.c", O_RDONLY);
	printf("fd : %d\n", fd);
	printf("%s\n", strerror(errno));
}