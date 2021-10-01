/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:21:39 by abelarif          #+#    #+#             */
/*   Updated: 2021/10/01 06:16:33 by abelarif         ###   ########.fr       */
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

    // //FOR DEBIAN
// char	*read_line(void)
// {
	// char	*line;
	// char	*prpt;

	// prpt = prompt();
	// // line = readline(prpt);
    // printf("%s", prpt);
    // get_next_line(1, &line);
	// if (line == NULL)
	// {
		// //FREE();
		// exit(EXIT_SUCCESS);
	// }
	// printf("liiiiine [%s]\n", line);
	// // if (empty_line(line) == 0)
		// // add_history(line);
	// free(prpt);
    // return (line);
// }

    //FOR MACOS
char	*read_line(void)
{
	char	*line;
	char	*prpt;

	prpt = prompt();
	rl_on_new_line();
	line = readline(prpt);
	if (line == NULL)
	{
		//FREE();
		exit(EXIT_SUCCESS);
	}
	// printf("liiiiine [%s]\n", line);
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
	tmp = ft_strjoin("\x1B[32mMINISHELL (\x1B[34m", pwd);
	prompt = ft_strjoin(tmp, "\x1B[32m) 🚀\x1B[0m ");
	free(tmp);
	tmp = ft_strjoin(prompt, "\x1B[37m");
	free(prompt);
	free(pwd);
	return (tmp);
}