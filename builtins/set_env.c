/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:52:21 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/10 14:56:31 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr[i]);
	arr[i] = NULL;
	free(arr);
}

char	**set_env(char *s0, char *s1)
{
	int		index;
	int		len;
	char	*new;
	
	index = -1;
	len = ft_strlen(s0);
	while (g_env.env[++index])
		if (strncmp(g_env.env[index], s0, len - 1) == 0
			&& g_env.env[index][len] == '=')
			break;		
	free_arr(g_env.sorted);
	if (g_env.env[index] == NULL)
	{
		// Later ... add_env(s0, s1);
	}
	else
	{
		free(g_env.env[index]);
		new = ft_strjoin(s0, "=");
		new = ft_strjoin(new, s1);
		g_env.env[index] = new;	
		sort_env();
	}
	return (g_env.env);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	i = -1;

	envp = set_env("SHELL", "HIHIHIHIHIHIHIHIHIHIHIHIIHIHI");
	while (envp[++i])
	{
		printf("aft : [%s]\n", envp[i]);
	}
	return (0);
}