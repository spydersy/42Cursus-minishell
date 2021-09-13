/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:21:39 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/13 11:09:41 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_window(void)
{
	write(1, "\e[1;1H\e[2J", ft_strlen("\e[1;1H\e[2J"));
}

int	empty_line(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			return (0);
		}
	}
	return (1);
}

    //FOR DEBIAN
// char	*read_line(void)
// {
// 	char	*line;
// 	char	*prpt;

// 	prpt = prompt();
// 	// line = readline(prpt);
//     get_next_line(1, &line);
// 	if (line == NULL)
// 	{
// 		//FREE();
// 		exit(EXIT_SUCCESS);
// 	}
// 	printf("liiiiine [%s]\n", line);
// 	// if (empty_line(line) == 0)
// 		// add_history(line);
// 	free(prpt);
//     return (line);
// }

    //FOR MACOS
char	*read_line(void)
{
	char	*line;
	char	*prpt;

	prpt = prompt();
	line = readline(prpt);
	if (line == NULL)
	{
		//FREE();
		exit(EXIT_SUCCESS);
	}
	printf("liiiiine [%s]\n", line);
	if (empty_line(line) == 0)
		add_history(line);
	free(prpt);
    return (line);
}

char	*prompt(void)
{
	char	*pwd;
	char	*prompt;
	char	*tmp;

	pwd = malloc(sizeof(char) * 500);
	pwd = getcwd(pwd, 500);
	tmp = ft_strjoin("\x1B[32m MINISHELL (\x1B[34m", pwd);
	prompt = ft_strjoin(tmp, "\x1B[32m) 🚀 ");
	free(tmp);
	tmp = ft_strjoin(prompt, "\x1B[37m");
	free(prompt);
	free(pwd);
	return (tmp);
}