/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:28:10 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/12 14:15:01 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	extract_pipe_line(char *line)
{
	int					i;
	t_separator			c_separator;
	int					error;

	i = -1;
	error = 0;
	c_separator = get_separator_index(line, '|');
	if (c_separator.nb_separator == 0)
		c_separator.content = ft_split(line, '\0');
	else
		c_separator.content = splitSep(line, c_separator.separator_index, c_separator.nb_separator);
	free(c_separator.separator_index);
	c_separator.separator_index = NULL;
	while (c_separator.content[++i])
	{
		if (c_separator.content[i][0] == '|' || c_separator.content[i][0] == ';')
			error = 1;
		printf("     command %d : [%s]\n", i, c_separator.content[i]);
		printf("\n");
	}
	if (error == 0)
		extract_tokens(c_separator.content);
	i = -1;
	while (c_separator.content[++i])
	{
		free(c_separator.content[i]);
		c_separator.content[i] = NULL;
	}
	free(c_separator.content);
	c_separator.content = NULL;
}

void	extract_semicolon_line(char *line)
{
	int				i;
	int				flag;
	t_separator		cl_separator;

	i = -1;
	flag = 0;
	if (ft_strlen(line) == 0)
	{
		free(line);
		line = NULL;
		return ;
	}
	cl_separator = get_separator_index(line, ';');
	if (cl_separator.nb_separator == 0)
		cl_separator.content = ft_split(line, '\0');
	else
		cl_separator.content = splitSep(line, cl_separator.separator_index, cl_separator.nb_separator);
	while (cl_separator.content[++i])
	{
		extract_pipe_line(cl_separator.content[i]);
		free(cl_separator.content[i]);
		free(cl_separator.separator_index);
		cl_separator.separator_index = NULL;
		cl_separator.content[i] = NULL;
	}
	free(cl_separator.content);
	free(line);
	line = NULL;
}
