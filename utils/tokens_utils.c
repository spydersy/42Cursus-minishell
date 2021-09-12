/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:06:45 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/12 10:02:00 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_tok(char *line, int nb)
{
	char	**tok;
	int		i;

	i = -1;
	tok = malloc(sizeof(char *) * (nb + 1));
	if (tok == NULL)
		ft_error("malloc", 1);
	tok[nb] = NULL;
	while (++i < nb)
	{
		tok[i] = get_token(line, i);
	}
	return (tok);
}

void	free_toks(t_tokens tok)
{
	int			i;

	i = -1;
	while (tok.tokens[++i])
	{
		free(tok.tokens[i]);
		tok.tokens[i] = NULL;
	}
	free(tok.tokens[i]);
	tok.tokens[i] = NULL;
	free(tok.tokens);
	tok.tokens = NULL;
}

void	set_tok_value(int *type, char **content)
{
	int		i;
	int		cmd;
	int		index;

	i = -1;
	cmd = 0;
	while (content[++i])
	{
		if (i == 0)
			index = 0;
		else
			index = 1;
		if (ft_strncmp(">", content[i] + index,
				max_of(1, ft_strlen(content[i] + index))) == 0)
			type[i] *= REDO0;
		else if (ft_strncmp("<", content[i] + index,
				max_of(1, ft_strlen(content[i] + index))) == 0)
			type[i] *= REDI0;
		else if (ft_strncmp(">>", content[i] + index,
				max_of(1, ft_strlen(content[i] + index))) == 0)
			type[i] *= REDO1;
		else if (i && ((-REDI0 <= type[i - 1] && type[i - 1] <= -REDO0)
				|| (REDO0 <= type[i - 1] && type[i - 1] <= REDI0)))
			type[i] *= FILE;
		else if (cmd == 0)
		{
			cmd = 1;
			type[i] *= CMD;
		}
		else
			type[i] *= ARG;
	}
}

int	    *set_tok_types(t_tokens tok)
{
	int			*type;

	type = malloc(sizeof(int) * tok.nb);
	if (type == NULL)
	{
		ft_error("set_tok_types", 1);
	}
	set_separator_type(type, tok.tokens);
	set_tok_value(type, tok.tokens);
	return (type);
}