/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:34:22 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/18 07:03:23 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_quote	init_quote(void)
{
	t_quote		quote;

	quote.s_quote = false;
	quote.d_quote = false;
	return (quote);
}

t_quote	set_quote_value(char quote_type, t_quote to_quote)
{
	t_quote		quote;

	quote.d_quote = to_quote.d_quote;
	quote.s_quote = to_quote.s_quote;
	if (to_quote.d_quote == false && to_quote.s_quote == false)
	{
		if (quote_type == 39)
			quote.s_quote = true;
		else
			quote.d_quote = true;
	}
	else if ((to_quote.s_quote == true) && (quote_type == 39))
		quote.s_quote = false;
	else if ((to_quote.d_quote == true) && (quote_type == 34))
		quote.d_quote = false;
	return (quote);
}

int	count_separators(char *line, char separator)
{
	int				i;
	t_quote			quote;
	int				c;

	c = 0;
	i = -1;
	quote = init_quote();
	while (line[++i])
	{
		if ((line[i] == 39 || line[i] == 34))
			if (count_bs(line, i) % 2 == 0)
				quote = set_quote_value(line[i], quote);
		if (separator == ';' && line[i] == ';' && line[i + 1] == ';')
			ft_error("syntax error near unexpected token `;;'", 0);
		else if (separator == '|' && line[i] == '|' && line[i + 1] == '|')
			ft_error("syntax error near unexpected token `|'", 0);
		else if (line[i] == separator)
			if (count_bs(line, i) % 2 == 0)
				if (!quote.s_quote && !quote.d_quote)
					c++;
	}
	return (c);
}

t_separator	get_separator_index(char *line, char separator_type)
{
	t_quote			quote;
	int				i;
	int				c;
	t_separator		separator;

	i = -1;
	c = -1;
	quote = init_quote();
	separator.separator_index = NULL;
	separator.nb_separator = count_separators(line, separator_type);
	separator.separator_index = malloc(separator.nb_separator * sizeof(int));
	if (separator.separator_index == NULL)
		ft_error(NULL, 1);
	while (line[++i])
	{
		if ((line[i] == 39 || line[i] == 34) && (count_bs(line, i) % 2 == 0))
			quote = set_quote_value(line[i], quote);
		else if (line[i] == separator_type && (count_bs(line, i) % 2 == 0))
			if (!quote.s_quote && !quote.d_quote
				&& c + 1 < separator.nb_separator)
				separator.separator_index[++c] = i;
	}
	return (separator);
}
