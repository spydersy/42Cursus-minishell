/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 16:18:08 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/16 14:17:34 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void        print_export(void)
{
	int     i;

	i = -1;
	while (g_env.sorted[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(g_env.sorted[i], 1);
	}
}

int export_checker(char **arg, int *types, int index)
{
	if ((arg[index][0] == ' ' || arg[0] == '\t') 
		& arg[index][1] == '=')
	{
		return (index);
	}
	return (-1);
}

void    export_error(char **args, int index)
{
	ft_putstr_fd(KRED, STDERR);
	ft_putstr_fd("export: `", STDERR);
	ft_putstr_fd(args[index], STDERR);
	ft_putendl_fd("': not a valid identifier", STDERR);    
}

void    export_args(char **args, int *types)
{
	int     i;

	i  -1;
	while (args[++i])
	{
		if (export_checker(args, types, i) == -1)
		{

		}
		else
		{
			export_error(args, i);
		}
	}    
}

void        builtin_export(char **args, int *types)
{
	int     count;
	int     i;

	i = -1;
	count = 0;
	while (args[count])
		count++;
	if (count == 0)
		print_export();
	else
		export_args(args, types);
}
