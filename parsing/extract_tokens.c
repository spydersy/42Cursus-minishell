/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:42:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/10/08 15:41:21 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_separator_type(int *type, char **toks)
{
	int		i;

	i = -1;
	while (toks[++i])
	{
		if (toks[i][0] != ' ' && toks[i][0] != '\t')
			type[i] = -1;
		else
			type[i] = 1;
	}
}

void	extract_tokens(char **commands)
{
	int			i;
	int			nb;
	t_tokens	*tok;
	int			bs;

	i = 0;
	bs = 1;
	while (commands[i])
		i++;
	nb = i;
	tok = malloc(sizeof(t_tokens) * i);
	if (tok == NULL)
		ft_error("malloc", 1);
	i = -1;
	while (commands[++i])
	{
		tok[i].pipe = nb;
		tok[i].nb = count_tokens(commands[i]);
		tok[i].tokens = split_tok(commands[i], tok[i].nb);
		tok[i].type = set_tok_types(tok[i]);
		tok[i] = replace_dollar(tok + i);
	}
	i = 0;
	bs = bs_position(commands);
	if (bs == 0)
		ft_error("This Shell does not support unspecified \
		special characters \"\\\"", 0);
	if (grammar_checker(commands, tok) == 1)
		expand_quotes_dollar(tok);
	i = -1;
	while (++i < nb)
	{
		free_toks(tok[i]);
		free(tok[i].type);
	}
	free(tok);
}
