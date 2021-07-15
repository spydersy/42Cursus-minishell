/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:36:06 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/11 17:11:07 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	max_of(int i, int j)
{
	if (i < j)
		return (j);
	else
		return (i);
}

void	sort_env(void)
{
	int		i;
	int		repeat;
	char	*tmp;

	tmp = NULL;
	repeat = 1;
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
	g_env.sorted = malloc(sizeof(char *) * (c + 1));
	if (g_env.env == NULL || g_env.sorted == NULL)
		ft_error("malloc", 1);
	g_env.size = c;
	c = -1;
	while (env[++c])
	{
		g_env.env[c] = ft_strdup(env[c]);
		g_env.sorted[c] = ft_strdup(env[c]);
		if (g_env.env[c] == NULL || g_env.sorted[c] == NULL)
			ft_error("malloc", 1);
	}
	g_env.env[c] = NULL;
	g_env.sorted[c] = NULL;
	sort_env();
}
