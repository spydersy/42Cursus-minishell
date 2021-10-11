/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 16:18:08 by abelarif          #+#    #+#             */
/*   Updated: 2021/10/11 16:27:10 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void        print_export(void)
{
	int     i;
    int     j;

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

// // int export_checker(char **arg, int *types, int index)
// // {
	// // if ((arg[index][0] == ' ' || arg[0] == '\t')
			// // & arg[index][1] == '=')
	// // {
		// // return (index);
	// // }
	// // return (-1);
// // }

// // void    export_error(char **args, int index)
// // {
	// // ft_putstr_fd(args[index], STDERR);
	// // ft_putendl_fd("': not a valid identifier", STDERR);
// // }

// void	export_errors_checker(char **args, int *types)
// {
	// int		i;

	// i = -1;
	// ft_putstr_fd(KRED, STDERR);
	// while (args[++i])
	// {
		// if (args[i][0] == '=')
		// {
			// ft_putstr_fd("export: `", STDERR);
			// ft_putstr_fd(args[i], STDERR);
			// if (args[i + 1] && types[i + 1] < 0)
			// {
				// ft_putstr_fd(args[i + 1], STDERR);
				// ft_putendl_fd("': not a valid identifier", STDERR);
				// i++;
			// }
		// }
	// }
	// ft_putstr_fd(KNRM, STDERR);
// }

// // int	value_exist(char **args, int *types, int index)
// // {
// // 	char	*str;
// // 	char	*tmp;

// // 	if (args[index + 1] && args[index + 1][0] != '=' && types[index + 1] < 0)
// // 	{
// // 		add_env(args[index], args[index + 1]);
// // 	}
// // 	else if (args[index + 1] && args[index + 1][0] != '=')
// // 		add_env(args[index], "");
// // 	return (index + 1);
// // }

// // void	export_handler(char **args, int *types, int start, int end)
// // {
// // 	int	i;
// // 	int	index;

// // 	i = -1;
// // 	while (args[++i])
// // 	{
// // 		index = 0;
// // 		if (args[i][index] != '=')
// // 		{
// // 			i = value_exist(args, types, i);
// // 		}
// // 	}
// // }

// int	get_start_index(int start, int end, char **args, int *types)
// {
	// (void)types;
	// if (start == 0)
		// return (0);
	// start = end;
	// if (args[start + 1])
	// {
		// return (++start);
	// }
	// return (start);
// }

// int	get_end_index(int start, int end, char **args, int *types)
// {
	// (void)args;
	// end = start + 1;
	// while (args[end] && types[end] < 0)
	// {
		// end++;
	// }
	// return (end);
// }

// void    export_args(char **args, int *types, int reset)
// {
	// static int start = 0;
	// static int end = 0;

	// if (reset == 1)
	// {
		// start = 0;
		// end = 0;
	// }
	// export_errors_checker(args, types);
	// while (args[end])
	// {
		// start = get_start_index(start, end, args, types);
		// end = get_end_index(start, end, args, types);
		// printf("EXPORT : [%d{%s} ~ %d{%s}]\n", start, args[start], end, args[end]);
		// sleep(3);
		// // export_handler(args, types, start, end);
	// }
// }

// int        builtin_export(char **args, int *types)
// {
	// int     count;
	// int     i;

	// i = -1;
	// count = 0;
	// while (args[count])
		// count++;
	// if (count == 0)
		// print_export();
	// else
		// export_args(args, types, 1);
	// return (0);
// }

void    print_error(char *wrong_arg)
{
    ft_putstr_fd(KRED, 2);
    ft_putstr_fd("export: `", 2);
    ft_putstr_fd(wrong_arg, 2);
    ft_putendl_fd("': not a valid identifier", 2);
}

void    print_export_errors(char **args)
{
    int i;

    i = -1;
    while (args[++i])
    {
        if (ft_isalpha(args[i][0]) && args[i][0] != '_')
        {
            print_error(args[i]);
        }
    }
}

int is_wrong_arg(char *arg)
{
    if (ft_isalpha(args[i][0]) && rgs[i][0] != '_')
    {
        return (1);
    }
    return (0);
}

char    *get_var(char *arg)
{
    int     end;
    char    *var;

    end = -1;
    while (arg[++end])
    {
        if (arg[end] == '=')
        {
            break;
        }
    }
    var = ft_substr(arg, 0, end);
    return (var);
}

char    *get_value(char *arg)
{
    int     start;
    char    *var;

    start = -1;
    while (arg[++start])
    {
        if (arg[start] == '=')
        {
            break;
        }
    }
    var = ft_strdup(arg + start + 1);
    return (var);
}

int export(char **args)
{
    int     i;
    char    *value;
    char    *var;
    int     wrong;

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
	char 	**new_args;

    if (count(args) == 0)
    {
        print_export();
        return (0);
    }
	new_args = join_args(args, types);
    print_export_errors(new_args);
    return (export(new_args));
}
