/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:28:27 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/17 14:27:00 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int	skip_new_line(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "-n"))
		{
			return (i);
		}	
	}
	return (i);
}

void	builtin_echo(char **args, int *types)
{
	int		i;
	int		counter;
	int		new_line;

	i = -1;
	new_line = 1;
	counter = count_arr(args);
	i = skip_new_line(args);
	if (i > 0)
		new_line = 0;
	i--;
	while (args[++i])
	{
		printf("%s", args[i]);
		if (types[i] > 0)
			printf(" ");
	}
	if (new_line == 1)
		printf("\n");
}
