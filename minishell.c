/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:09:10 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/17 14:22:41 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	printf("SIIIIIIIIIIIIIGNAL : [%d]\n", sig);
	terminal_view();
	sig = 0;
}

void	signal_handler(int sig)
{
	// if (signal(SIGINT, ctrl_c) == SIG_ERR)
		// exit(1);
	// ctrl_c(sig);
	char	*prpt;
	if (sig == SIGINT)
	{
		prpt = prompt();
		ft_putchar_fd('\n', 1);
		ft_putstr_fd(prpt, 1);
		// ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_putchar_fd('\r', 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

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
		if (empty_line(line) == 0)
		{
			extract_semicolon_line(line);
			// free(line);
		}
		else
			free(line);
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
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	terminal_view();
	free_env();
}
