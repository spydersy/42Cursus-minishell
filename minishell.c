/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:09:10 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/11 17:05:12 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal_view(void)
{
	static int	first_time = 1;

	while (1)
	{
		signal(SIGINT, prompt);
		if (first_time)
		{
			clear_window();
			first_time = 0;
		}
		prompt(0);
		extract_semicolon_line(read_line());
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
