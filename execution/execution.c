/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:45:33 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/13 16:59:11 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	print_args2(char **args, int *types, char **files)
{
	int		i;

	i = -1;
	printf("ARGS  :");
	while (args[++i])
	{
		printf(" [%s, %d] ", args[i], types[i]);
		free(args[i]);
	}
	printf("\n");
	printf("FILES :");
	i = -1;
	while (files[++i])
	{
		printf(" [%s] ", files[i]);
		free(files[i]);
	}
	printf("\n");
	free(args);
	free(files);
}

char	**get_execution_args(t_tokens tokens)
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
	args[c] = NULL;
	i = -1;
	c = 0;
	while (++i < tokens.nb)
	{
		if ((tokens.type[i] == ARG || tokens.type[i] == -ARG) && (tokens.tokens[i][0] == ' ' || tokens.tokens[i][0] == '\'' || tokens.tokens[i][0] == '\"'))
		{
			args[c++] = ft_strdup(tokens.tokens[i] + 1);
		}
		else if (tokens.type[i] == -ARG || tokens.type[i] == ARG)
			args[c++] = ft_strdup(tokens.tokens[i]);
		else if (tokens.type[i] == PROTECTED0 || tokens.type[i] == -PROTECTED0
			|| tokens.type[i] == PROTECTED1 || tokens.type[i] == -PROTECTED1)
		{
			args[c++] = ft_strdup(tokens.tokens[i]);
		}
	}
	return (args);
}

int	*get_execution_types(t_tokens tokens)
{
	int		i;
	int		c;
	int		*types;
	
	c = 0;
	i = -1;
	while (++i < tokens.nb)
		if (tokens.type[i] == ARG || tokens.type[i] == -ARG
			|| tokens.type[i] == PROTECTED0 || tokens.type[i] == -PROTECTED0
			|| tokens.type[i] == PROTECTED1 || tokens.type[i] == -PROTECTED1)
			c++;
	types = malloc(sizeof(int) * c);
	i = -1;
	c = 0;
	while (++i < tokens.nb)
		if (tokens.type[i] == ARG || tokens.type[i] == -ARG
			|| tokens.type[i] == PROTECTED0 || tokens.type[i] == -PROTECTED0
			|| tokens.type[i] == PROTECTED1 || tokens.type[i] == -PROTECTED1)
			types[c++] = tokens.type[i];
	return (types);
}

char	**get_execution_files(t_tokens tokens)
{
	int		i;
	int		c;
	char	**files;
	
	i = -1;
	c = 0;
	while (++i < tokens.nb)
		if (tokens.type[i] == FILE || tokens.type[i] == -FILE)
			c++;
	files = malloc(sizeof(char *) * (c + 1));
	files[c] = NULL;
	i = -1;
	c = 0;
	while (++i < tokens.nb)
	{
		if (tokens.type[i] == FILE || tokens.type[i] == -FILE)
			files[c++] = ft_strdup(tokens.tokens[i] + 1);
	}
	return (files);
}

t_execution *init_execution(t_tokens *tokens)
{
	int             i;
	t_execution     *execution;

	i = -1;
	execution = malloc(sizeof(t_execution) * tokens[0].pipe);
	while (++i < tokens[0].pipe)
	{
		printf("****************************************************\n");
		execution[i].nb_pipelines = tokens[0].pipe;
		execution[i].exec_path = get_exec_path(tokens[i], get_paths());
		execution[i].args = get_execution_args(tokens[i]);
		execution[i].args_type = get_execution_types(tokens[i]);
		execution[i].files = get_execution_files(tokens[i]);
		printf("exec_path : [%s]\n", execution[i].exec_path);
		print_args2(execution[i].args, execution[i].args_type, execution[i].files);
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
