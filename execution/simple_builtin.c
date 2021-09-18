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

t_execution	*simple_builtin(t_execution *execution)
{
	if (!ft_strcmp(execution[0].exec_path, "builtin_cd"))
		builtin_cd(execution[0].args + 1);
	if (!ft_strcmp(execution[0].exec_path, "builtin_echo"))
		builtin_echo(execution[0].args + 1, execution[0].args_type + 1);
	if (!ft_strcmp(execution[0].exec_path, "builtin_env"))
		builtin_env();
	if (!ft_strcmp(execution[0].exec_path, "builtin_exit"))
		builtin_exit(execution[0].args + 1);

	// if (!ft_strcmp(execution[0].exec_path, "builtin_export"))
		// builtin_export(execution[0].args, execution[0].args_type);

	if (!ft_strcmp(execution[0].exec_path, "builtin_pwd"))
		builtin_pwd(0);
	if (!ft_strcmp(execution[0].exec_path, "builtin_unset"))
		builtin_unset(execution[0].args + 1);
	



	return (execution);
}