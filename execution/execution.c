/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:45:33 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/11 18:41:21 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_tokens *tokens)
{
	int				i;
	t_execution		*execution;

	i = -1;
	execution = malloc(sizeof(t_execution) * tokens[0].pipe);
	
	printf("INSIDE EXECUTION : %d\n", tokens[0].pipe);
	while (++i < tokens[0].pipe)
	{
		execution[i].nb_pipelines = tokens[0].pipe;
		execution[i].exec_path = get_exec_path(tokens[i], get_paths());
		printf("exec_path : [%s]\n", execution[i].exec_path);
		free(execution[i].exec_path);
	}
	free(execution);
	printf("XXXXXXXX");
}