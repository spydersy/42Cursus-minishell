/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 14:41:22 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/18 14:43:51 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int     main()
{
	int	ret;
	char	*argv[] = {"cat", "main.c", "../main.c", NULL};
	char	*path = NULL;

	ret = execve(path, argv, NULL);
	printf("DONE %d\n", ret);
	return (0);
}
