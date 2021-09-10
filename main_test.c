/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 12:15:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/10 18:37:08 by abelarif         ###   ########.fr       */
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

// int	main(int argc, char *argv[])
// {
// 	int		ret;
// 	char	*buffer;
	
// 	ret = 0;
// 	ret = chdir(argv[1]);
// 	printf("ret : [%d]\n", ret);
// 	if (ret == -1)
// 	{
// 		printf("[%d],[%s]\n", errno, strerror(errno));
// 		// perror(buffer);
// 	}
// 	return (0);
// }



int		main()
{
	char	*buffer;
	while (1)
	{
		buffer = readline("PROMPT >>");
		if (buffer == NULL)
			exit(0);		
		printf("[%s]\n", buffer);
		add_history (buffer);
		free(buffer);
	}
	return (0);
}

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

// int		main(int argc, char *argv[])
// {
// 	char		*sub;

// 	sub = ft_substr("   $SHELL vfsdv", 3, 6);
// 	printf("[%s]\n", sub);

// 	return (0);
// }

// int		main()
// {
// 	char	*args[] = {"/bin/ls", NULL};
//     char    *buffer;

// 	int ret = execve(args[1], args, NULL);
//     perror(buffer);
// 	printf("FATAL %d\n", ret);
// 	printf("[%s]\n", strerror(errno));
// 	return (0);
// }

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
