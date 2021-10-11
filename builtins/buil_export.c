/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 16:18:08 by abelarif          #+#    #+#             */
/*   Updated: 2021/10/11 17:12:04 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(void)
{
	int		i;
	int		j;

	i = -1;
	while (g_env.sorted[++i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		j = -1;
		while (g_env.sorted[i][++j])
		{
			if (g_env.sorted[i][j] == '=')
			{
				ft_putchar_fd("\"", STDOUT);
			}
			ft_putchar_fd(g_env.sorted[i][j], STDOUT);
		}
		ft_putstr_fd("\"\n", STDOUT);
	}
}

void	print_error(char *wrong_arg)
{
	ft_putstr_fd(KRED, 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(wrong_arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	print_export_errors(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
	{
		if (ft_isalpha(args[i][0]) && args[i][0] != '_')
		{
			print_error(args[i]);
		}
	}
}

int	is_wrong_arg(char *arg)
{
	if (ft_isalpha(args[i][0]) && rgs[i][0] != '_')
	{
		return (1);
	}
	return (0);
}

char	*get_var(char *arg)
{
	int		end;
	char	*var;

	end = -1;
	while (arg[++end])
	{
		if (arg[end] == '=')
		{
			break ;
		}
	}
	var = ft_substr(arg, 0, end);
	return (var);
}

char	*get_value(char *arg)
{
	int		start;
	char	*var;

	start = -1;
	while (arg[++start])
	{
		if (arg[start] == '=')
		{
			break ;
		}
	}
	var = ft_strdup(arg + start + 1);
	return (var);
}

int	export(char **args)
{
	int		i;
	char	*value;
	char	*var;
	int		wrong;

	i = -1;
	wrong = 0;
	while (args[++i])
	{
		if (is_wrong_arg(arg[i]) == 0)
		{
			var = get_var(arg);
			value = get_value(arg);
			add_env(var, value);
			free(var);
			free(value);
		}
		else
			wrong = 1;
	}
	free_arr(args);
	return (wrong);
}

int	builtin_export(char **args, int *types)
{
	char	**new_args;

	if (count(args) == 0)
	{
		print_export();
		return (0);
	}
	new_args = join_args(args, types);
	print_export_errors(new_args);
	return (export(new_args));
}
