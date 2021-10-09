/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:35:26 by abelarif          #+#    #+#             */
/*   Updated: 2021/10/09 16:39:53 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	free_dollar(char **old, char **content)
{
	int		i;

	i = -1;
	while (old[++i])
	{
		free(old[i]);
		old[i] = NULL;
	}
	i = -1;
	while (content[++i])
	{
		free(content[i]);
		content[i] = NULL;
	}
	free(old);
	free(content);
	old = NULL;
	content = NULL;
}

void	free_execution(t_execution *execution)
{
	int		i;
	int		j;

	i = -1;
	while (++i < execution[0].nb_pipelines)
	{
		j = -1;
		while (execution[i].args[++j])
			free(execution[i].args[j]);
		free(execution[i].args[j]);
		free(execution[i].args);
		free(execution[i].args_type);
		j = -1;
		while (execution[i].files[++j])
			free(execution[i].files[j]);
		free(execution[i].files[j]);
		free(execution[i].files);
		if (execution[i].command != NULL)
			free(execution[i].command);
		if (execution[i].exec_path != NULL)
			free(execution[i].exec_path);
		free(execution[i].files_type);
	}
	free(execution);
}
