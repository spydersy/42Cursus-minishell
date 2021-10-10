/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   original_fuonction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:22:28 by abelarif          #+#    #+#             */
/*   Updated: 2021/10/10 16:24:13 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	replace_dollar(t_tokens *tok)
{
	int			i;
	int			presence;
	int			oldlen;
	int			newlen;

	presence = 1;
	oldlen = count(tok->tokens);
	newlen = oldlen;
	i = -1;
	while (presence)
	{
		presence = 0;
		while (tok->tokens[++i])
		{
			if ((tok->tokens[i][1] == '$' && i)
				|| (i == 0 && tok->tokens[i][0] == '$'))
			{
				dollar_handling(&(tok->tokens[i]), i);
				tok->tokens = split_dollar_signe(tok->tokens, i);
				presence = 1;
				newlen = count(tok->tokens);
				if (oldlen != newlen)
					set_types(tok, oldlen, newlen, i);
				else if (tok->type[i] < 0)
					tok->type[i] = -PROTECTED0;
				else
					tok->type[i] = PROTECTED0;
				if (tok->type[0] == PROTECTED0 || tok->type[0] == -PROTECTED0)
					tok->type[i] = -CMD;
				i += newlen - oldlen;
				oldlen = newlen;
				break ;
			}
		}
		tok->nb = i;
	}
	return (*tok);
}
