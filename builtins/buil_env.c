/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:43:02 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/17 14:27:14 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	eq_exist(char *env_var)
{
	int		i;
	
	i = -1;
	while (env_var[++i])
	{
		if (env_var[i] == '=')
			return (1);
	}
	return (0);
}

int	builtin_env(void)
{
	int		i;

	i = 0;
	while (g_env.env[++i])
	{
		if (eq_exist(g_env.env[i]) == 1)
			printf("%s\n", g_env.env[i]);
	}
	return (0);
}
