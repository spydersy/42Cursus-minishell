/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:45:33 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/13 11:27:15 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



char    **get_execution_args(t_tokens tokens)
{
	int     i;
	int     c;
	char    **args;

	i = -1;
	c = 0;
	while (++i < tokens.nb)
		if (tokens.type[i] == ARG || tokens.type[i] == -ARG
			|| tokens.type[i] == PROTECTED0 || tokens.type[i] == -PROTECTED0
			|| tokens.type[i] == PROTECTED1 || tokens.type[i] == -PROTECTED1)
			c++;
	args = malloc(sizeof(char *) * (c + 1));
	i = -1;
	while (++i < tokens.nb)
	{
		if (tokens.type[i] == ARG || tokens.type[i] == -ARG)
		{

		}
		else if (tokens.type[i] == PROTECTED0 || tokens.type[i] == -PROTECTED0)
		{

		}
		else if (tokens.type[i] == PROTECTED1 || tokens.type[i] == -PROTECTED1)
		{

		}
	}
	return NULL;	
}


t_execution *init_execution(t_tokens *tokens)
{
	int             i;
	t_execution     *execution;

	i = -1;
	execution = malloc(sizeof(t_execution) * tokens[0].pipe);
	printf("DBG NB : [%d][%d]\n", tokens[0].nb, tokens[0].pipe);
	while (++i < tokens[0].pipe)
	{
		execution[i].nb_pipelines = tokens[0].pipe;
		execution[i].exec_path = get_exec_path(tokens[i], get_paths());
		// execution[i].args = get_execution_args(tokens[i]);
		printf("exec_path : [%s]\n", execution[i].exec_path);
		free(execution[i].exec_path);
	}
	free(execution);
	printf("XXXXXXXX");
	return (execution);
}

void    execution(t_tokens *tokens)
{
	// t_execution     *execution;

	init_execution(tokens);
}
