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

int	ft(t_tokens *tok, int *i, t_x_y_z *xyz)
{
	if ((tok->tokens[*i][1] == '$' && *i)
				|| (*i == 0 && tok->tokens[*i][0] == '$'))
	{
		dollar_handling(&(tok->tokens[*i]), *i);
		tok->tokens = split_dollar_signe(tok->tokens, *i);
		xyz->x = 1;
		xyz->z = count(tok->tokens);
		if (xyz->y != xyz->z)
			set_types(tok, xyz->y, xyz->z, *i);
		else if (tok->type[*i] < 0)
			tok->type[*i] = -PROTECTED0;
		else
			tok->type[*i] = PROTECTED0;
		if (tok->type[0] == PROTECTED0 || tok->type[0] == -PROTECTED0)
			tok->type[*i] = -CMD;
		(*i) += xyz->z - xyz->y;
		xyz->y = xyz->z;
		return (1);
	}
	return (0);
}

// X = PRESENCE
// Y = OLDLEN
// Z = NEWLEN

t_tokens	replace_dollar(t_tokens *tok)
{
	int			i;
	t_x_y_z		xyz;

	xyz.x = 1;
	xyz.y = count(tok->tokens);
	xyz.z = xyz.y;
	i = -1;
	while (xyz.x)
	{
		xyz.x = 0;
		while (tok->tokens[++i])
		{
			if (ft(tok, &i, &xyz) == 1)
				break ;
		}
		tok->nb = i;
	}
	return (*tok);
}
