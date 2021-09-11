/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:36:06 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/11 15:44:04 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	arr_dup(void)
{
	int	i;

	i = 0;
	while (g_env.env[i])
		i++;
	g_env.sorted = malloc(sizeof(char *) * (i + 1));
	g_env.sorted[i] = NULL;
	i = -1;
	while (g_env.env[++i])
	{
		g_env.sorted[i] = ft_strdup(g_env.env[i]);
		printf(">>%s<<\n", g_env.sorted[i]);
	}
}

void	sort_env(void)
{
	int		i;
	int		repeat;
	char	*tmp;

	tmp = NULL;
	repeat = 1;
	arr_dup();
	while (repeat)
	{
		i = -1;
		repeat = 0;
		while (g_env.sorted[++i])
		{
			if (g_env.sorted[i] && g_env.sorted[i + 1]
				&& ft_strncmp(g_env.sorted[i], g_env.sorted[i + 1],
					max_of(ft_strlen(g_env.sorted[i]),
						ft_strlen(g_env.sorted[i + 1]))) > 0)
			{
				tmp = g_env.sorted[i];
				g_env.sorted[i] = g_env.sorted[i + 1];
				g_env.sorted[i + 1] = tmp;
				repeat = 1;
			}
		}
	}
}

void	init_env(char **env)
{
	int		c;

	c = 0;
	while (env[c])
		c++;
	g_env.env = malloc(sizeof(char *) * (c + 1));
	if (g_env.env == NULL)
		ft_error("malloc", 1);
	g_env.size = c;
	c = -1;
	while (env[++c])
	{
		g_env.env[c] = ft_strdup(env[c]);
		if (g_env.env[c] == NULL)
			ft_error("malloc", 1);
	}
	g_env.env[c] = NULL;
	sort_env();
}
