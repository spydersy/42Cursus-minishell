/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 12:15:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/07 08:20:44 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "minishell.h"
/*char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		sub = (char *)malloc(sizeof(char));
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
*/


// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*sub;

// 	if (!s)
// 		return (NULL);
// 	if (start > ft_strlen(s))
// 	{
// 		sub = (char *)malloc(sizeof(char));
// 		if (sub == NULL)
// 			return (NULL);
// 		sub[0] = '\0';
// 		return (sub);
// 	}
// 	else if (len > ft_strlen(s + start))
// 		len = ft_strlen(s + start);
// 	sub = (char *)malloc(sizeof(char) * len + 1);
// 	if (sub == NULL)
// 		return (NULL);
// 	ft_strlcpy(sub, s + start, len + 1);
// 	return (sub);
// }

int		main(int argc, char *argv[])
{
	char		*sub;

	sub = ft_substr("   $SHELL vfsdv", 3, 6);
	printf("[%s]\n", sub);

	return (0);
}

/*int		main()
{
	char	*args[] = {"addd.out", NULL};
    char    *buffer;

	execve(args[1], args, NULL);
    perror(buffer);
	printf("FATAL\n");
	return (0);
}
*/
/*
int main()
{
    int             ret;
    struct stat     statbuf;

    ret = stat("main.c", &statbuf);
    printf("%u\n", statbuf.st_mode);
    printf("ret : %d\n", ret);
    return (0);
}
*/
