/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:26:02 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/18 17:35:38 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	simple_builtin(t_execution *execution, int exit_flag)
{
	if (!ft_strcmp(execution[0].exec_path, "builtin_cd"))
		return (builtin_cd(execution[0].args + 1));
	else if (!ft_strcmp(execution[0].exec_path, "builtin_echo"))
		return (builtin_echo(execution[0].args + 1, execution[0].args_type + 1));
	else if (!ft_strcmp(execution[0].exec_path, "builtin_env"))
		return (builtin_env());
	else if (!ft_strcmp(execution[0].exec_path, "builtin_exit"))
		return (builtin_exit(execution[0].args + 1, exit_flag));
	else if (!ft_strcmp(execution[0].exec_path, "builtin_pwd"))
	{
		builtin_pwd(0);
		return (0);
	}
	else if (!ft_strcmp(execution[0].exec_path, "builtin_unset"))
		return (builtin_unset(execution[0].args + 1));
	else
		return (builtin_export(execution[0].args, execution[0].args_type));
}