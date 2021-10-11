/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 16:18:08 by abelarif          #+#    #+#             */
/*   Updated: 2021/10/09 17:13:39 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void        print_export(void)
// {
	// int     i;

	// i = -1;
	// while (g_env.sorted[++i])
	// {
		// ft_putstr_fd("declare -x ", 1);
		// ft_putendl_fd(g_env.sorted[i], 1);
	// }
// }

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

char	*init_args(char **args, int *types, int index)
{
	char	*arg;
	char	*tmp;

	tmp = ft_strdup(args[index]);
	while (args[++index] && types[index] < 0)
	{
		arg = ft_strjoin(tmp, args[index]);
		free(tmp);
		tmp = ft_strdup(arg);
		free(arg);
	}
	return (tmp);
}

int	get_next_index(char **args, int *types, int index)
{
	while (args[++index])
	{
		if (types[index] > 0)
		{
			return (index);
		}
	}
	return (index);
}

char	**append_arg(char *arg, char **arr)
{
	int		i;
	char	**new_arr;

	i = count(arr);
	new_arr = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (arr && arr[++i])
	{
		new_arr[i] = ft_strdup(arr[i]);
	}
	new_arr[i++] = ft_strdup(arg);
	new_arr[i] = NULL;
	if (arr != NULL)
		free_arr(arr);
	free(arg);
	arr = new_arr;
	return (arr);
}

int	builtin_export(char **args, int *types)
{
	int		index;
	char 	**new_args;
	char 	*arg;

	index = 0;
	new_args = malloc(sizeof(char *) * 1);
	new_args[0] = NULL;
	arg = init_args(args, types, index);
	new_args = append_arg(arg, new_args);
	index = get_next_index(args, types, index);
	while (args[index])
	{
		arg = init_args(args, types, index);
		// printf("B\n");
		new_args = append_arg(arg, new_args);
		// printf("C\n");
		index = get_next_index(args, types, index);
		// printf("D\n");
	}
	int i = -1;
	while (new_args[++i])
	{
		printf("[%s] ", new_args[i]);
	}
	printf("\n");
	free_arr(new_args);
	return (0);
}
