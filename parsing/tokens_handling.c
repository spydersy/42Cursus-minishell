/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:16:03 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 10:14:54 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int						skip_spaces(char *line, int index)
{
	while (line[index])
	{
		if (line[index] == ' ' || line[index] == '\t')
			index++;
		else
			return (index);
	}
	return (index);
}

int						token_dollar(char *line, int index)
{
	if (line[index + 1] && line[index + 1] == '$')
        return (index + 2);
    index++;
    while (line[index])
    {
        if (line[index] == '$' || line[index] == ' ' || line[index] == '\t'
            || line[index] == '\'' || line[index] == '\"' || line[index] == '>'
            || line[index] == '<' || line[index] == '\0')
            return (index);
        else
            index++;
    }
    return (index);
}

int						token_word(char *line, int index)
{
	while (line[index])
    {
        if (line[index] == '$' || line[index] == ' ' || line[index] == '\t'
			|| line[index] == '>'
            || line[index] == '<' || line[index] == '\0')
                return (index);
        else if ((line[index] == '\'' || line[index] == '\"') && (count_bs(line, index) % 2 == 0))
			return (index);
		else
            index++;
    }
    return (index);
}

int						token_quotes(char *line, int index)
{
    int         i;

    i = index + 1;
	while (line[i])
    {
		if (line[i] == line[index] && line[index] == '\'')
            return (i + 1);
        if (line[i] == line[index] && (count_bs(line, i) % 2 == 0))
            return (i + 1);
		i++;
    }
    return (-1);
}

int						token_redir(char *line, int index)
{
	int					i;

	i = index;
	while (line[i])
	{
		if (line[i] == line[index])
		{
			i++;
		}
		else
			return (i);
	}
	return (i);
}

int						get_end(char *line, int index)
{

	if ((line[index] == '>' || line[index] == '<')
	&& count_bs(line, index) % 2 == 0)
	{
		index = token_redir(line, index);
	}
	else if (line[index] == '$'
	&& count_bs(line, index) % 2 == 0)
	{
		index = token_dollar(line, index);
	}
	else if (line[index] == '\'' || line[index] == '\"')
	{
		index = token_quotes(line, index);
        if (index == -1)
            ft_error("This Shell does not support unclosed quotes.", 0);
	}
	else
	{
		index = token_word(line, index);
	}
	return (index);
}

int						count_tokens(char *line)
{
	int		i;
	int		c;

	c = 0;
	i = 0;
	while (line[i])
	{
		if (line[i])
		{
			i = skip_spaces(line, i);
		}
		if (line[i])
		{
			i = get_end(line , i);
			if (i == -1)
				return (c);
			c++;
		}
		else
			return (c);
	}
    return (c);
}

char					*get_token(char *line, int flag)
{
	static int 			start = 0;
	char				*token;
	int					end = 0;
	int					bef;

	token = NULL;
	bef = 1;
	if (flag == 0)
		start = 0;
	if (start == 0)
		bef = 0;
	while (line[start])
	{
		start = skip_spaces(line, start);
		if (line[start])
		{
			end = get_end(line, start);
			if (end != -1)
				token = ft_subtoken(line, start - bef, end);
			start = end;
			return (token);
		}
	}
	return (token);
}
