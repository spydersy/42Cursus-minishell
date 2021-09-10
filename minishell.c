/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:09:10 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/09 18:05:16 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	signal_handler(int sig)
// {
// 	printf("signal : %d\n", sig);
// 	if (sig == 2)
// 	{
// 		readline(prompt());
// 	}
// }

void	terminal_view(void)
{
	static int	first_time = 1;
	char		*line;
	
	while (1)
	{
		if (first_time)
		{
			clear_window();
			first_time = 0;
		}
		line = read_line();
		extract_semicolon_line(line);
	}	
}

void	free_env(void)
{
	int		i;

	i = -1;
	while (g_env.env[++i])
	{
		free(g_env.env[i]);
		free(g_env.sorted[i]);
		g_env.env[i] = NULL;
		g_env.sorted[i] = NULL;
	}
	free(g_env.env);
	free(g_env.sorted);
	g_env.env = NULL;
	g_env.sorted = NULL;
}

void	minishell(int argc, char *argv[], char *envp[])
{	
	if (argv[1] != NULL || argc != 1)
	{
		ft_error("Arguments", 1);
	}
	init_env(envp);
	terminal_view();
	free_env();
}
