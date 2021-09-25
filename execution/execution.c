/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:45:33 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/20 07:43:05 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_args2(char **args, int *types, char **files, int *files_type, int *fds)
{
	int		i;

	i = -1;
	printf("ARGS  :");
	while (args[++i])
	{
		printf(" [%s, %d] ", args[i], types[i]);
		// free(args[i]);
	}
	printf("\n");
	printf("FILES :");
	i = -1;
	while (files[++i])
	{
		printf(" [%s, %d, %d] ", files[i], files_type[i], fds[i]);
		// free(files[i]);
	}
	printf("\n");
	// free(args);
	// free(types);
	// free(files_type);
	// free(files);
}

char	**get_execution_args(t_tokens tokens, char *command)
{
	int		i;
	int		c;
	char	**args;

	i = -1;
	c = 0;
	while (++i < tokens.nb)
		if (tokens.type[i] == ARG || tokens.type[i] == -ARG
			|| tokens.type[i] == PROTECTED0 || tokens.type[i] == -PROTECTED0
			|| tokens.type[i] == PROTECTED1 || tokens.type[i] == -PROTECTED1)
			c++;
	args = malloc(sizeof(char *) * (c + 2));
	args[0] = ft_strdup(command);
	args[c + 1] = NULL;
	i = -1;
	c = 0;
	while (++i < tokens.nb)
	{
		if ((tokens.type[i] == ARG || tokens.type[i] == -ARG)
			&& (tokens.tokens[i][0] == ' '
			|| tokens.tokens[i][0] == '\'' || tokens.tokens[i][0] == '\"'))
		{
			args[++c] = ft_strdup(tokens.tokens[i] + 1);
		}
		else if (tokens.type[i] == -ARG || tokens.type[i] == ARG)
			args[++c] = ft_strdup(tokens.tokens[i]);
		else if (tokens.type[i] == PROTECTED0 || tokens.type[i] == -PROTECTED0
			|| tokens.type[i] == PROTECTED1 || tokens.type[i] == -PROTECTED1)
		{
			args[++c] = ft_strdup(tokens.tokens[i]);
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
	types = malloc(sizeof(int) * (c + 1));
	i = -1;
	c = 0;
	types[0] = CMD;
	while (++i < tokens.nb)
		if (tokens.type[i] == ARG || tokens.type[i] == -ARG
			|| tokens.type[i] == PROTECTED0 || tokens.type[i] == -PROTECTED0
			|| tokens.type[i] == PROTECTED1 || tokens.type[i] == -PROTECTED1)
			types[++c] = tokens.type[i];
	return (types);
}

int	*get_execution_files_type(t_tokens tokens)
{
	int		i;
	int		c;
	int		*types;
	
	i = -1;
	c = 0;
	while (++i < tokens.nb)
		if (tokens.type[i] == FILE || tokens.type[i] == -FILE
			|| tokens.type[i] == EOFHEREDOC || tokens.type[i] == -EOFHEREDOC)
			c++;
	types = malloc(sizeof(char *) * c);
	i = -1;
	c = 0;
	while (++i < tokens.nb)
	{
		if (tokens.type[i] == FILE || tokens.type[i] == -FILE
			|| tokens.type[i] == EOFHEREDOC || tokens.type[i] == -EOFHEREDOC)
			types[c++] = tokens.type[i - 1];
	}
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
		if (tokens.type[i] == FILE || tokens.type[i] == -FILE
			|| tokens.type[i] == EOFHEREDOC || tokens.type[i] == -EOFHEREDOC)
			c++;
	files = malloc(sizeof(char *) * (c + 1));
	files[c] = NULL;
	i = -1;
	c = 0;
	while (++i < tokens.nb)
	{
		if (tokens.type[i] == FILE || tokens.type[i] == -FILE
			|| tokens.type[i] == EOFHEREDOC || tokens.type[i] == -EOFHEREDOC)
			files[c++] = ft_strdup(tokens.tokens[i] + 1);
	}
	return (files);
}

char	*get_exec_command(t_tokens tokens)
{
	int		i;
	
	i = -1;
	while (tokens.tokens[++i])
	{
		if (tokens.type[i] == CMD || tokens.type[i] == -CMD)
			return (ft_strdup(tokens.tokens[i]));
	}
	return (NULL);
}

t_execution *init_execution(t_tokens *tokens)
{
	int             i;
	t_execution     *execution;

	i = -1;
	execution = malloc(sizeof(t_execution) * tokens[0].pipe);
	while (++i < tokens[0].pipe)
	{
		execution[i].nb_pipelines = tokens[0].pipe;
		execution[i].command = get_exec_command(tokens[i]);
		execution[i].exec_path = get_exec_path(tokens[i], get_paths());
		execution[i].args = get_execution_args(tokens[i], execution[i].command);
		execution[i].args_type = get_execution_types(tokens[i]);
		execution[i].files = get_execution_files(tokens[i]);
		execution[i].files_type = get_execution_files_type(tokens[i]);
	}
	return (execution);
}

t_execution	*cases_redirection(t_execution *execution)
{
	if (execution[0].exec_path
		&& ft_strncmp(execution[0].exec_path, "builtin", 7) == 0
		&& execution[0].nb_pipelines == 1)
	{
		printf("BBBBBBBBBBBBBBBBBBBBBBB\n");
		return (simple_builtin(execution));
	}
	else
		return (execute_line(execution));
}

void    execution(t_tokens *tokens)
{
	t_execution     *execution;
	int		i = -1;
	
	execution = init_execution(tokens);
	while (++i < tokens[0].pipe)
	{
		// printf("****************************************************\n");
		// printf("exec_path : [%s] | command : [%s]\n", execution[i].exec_path, execution[i].command);
		// print_args2(execution[i].args, execution[i].args_type, execution[i].files, execution[i].files_type);
		// free(execution[i].exec_path);
	}
	// heredocs_parsing(execution);
	execution = cases_redirection(execution);
	free(execution);
}
