/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:42:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 09:43:38 by abelarif         ###   ########.fr       */
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

int	*set_tok_types(t_tokens tok)
{
	int			i;
	int			*type;

	i = -1;
	type = malloc(sizeof(int) * tok.nb);
	if (type == NULL)
	{
		ft_error("set_tok_types", 1);
	}
	set_separator_type(type, tok.tokens);
	set_tok_value(type, tok.tokens);
	return (type);
}

int     bs_position(char **tokens)
{
    int         i;
    int         j;
    t_quote     q;

    i = -1;
    while (tokens[++i])
    {
        j = -1;
        q = init_quote();
        while (tokens[i][++j])
        {
            if (tokens[i][j] == '\\' && q.d_quote == false && q.s_quote == false)
                return (0);
            if (tokens[i][j] == '\'' || tokens[i][j] == '\"')
            {
				q = set_quote_value(tokens[i][j], q);
            }
        }
    }
    return (1);
}

void	print_types(int *types, int nb, char **tokens)
{
	int		i;

	i = -1;
	while (++i < nb)
	{
		else if (types[i] == CMD || types[i] == -CMD)
			printf("type[%d] , %d [%s]: [CMD]\n", i, types[i], tokens[i]);
		else if (types[i] == ARG || types[i] == -ARG)
			printf("type[%d] , %d [%s]: [ARG]\n", i, types[i], tokens[i]);
		else if (types[i] == REDO0 || types[i] == -REDO0)
			printf("type[%d] , %d [%s]: [>]\n", i, types[i], tokens[i]);
		else if (types[i] == REDO1 || types[i] == -REDO1)
			printf("type[%d] , %d [%s]: [>>]\n", i, types[i], tokens[i]);
		else if (types[i] == REDI0 || types[i] == -REDI0)
			printf("type[%d] , %d [%s]: [<]\n", i, types[i], tokens[i]);
		else if (types[i] == FILE || types[i] == -FILE)
			printf("type[%d] , %d [%s]: [FILE]\n", i, types[i], tokens[i]);
		else if (types[i] == PROTECTED0 || types[i] == -PROTECTED0)
			printf("type[%d] , %d [%s]: [PROTEC0]\n", i, types[i], tokens[i]);
		else if (types[i] == PROTECTED1 || types[i] == -PROTECTED1)
			printf("type[%d] , %d [%s]: [PROTEC1]\n", i, types[i], tokens[i]);
		else
			printf("type[%d] , %d [%s]: [random]\n", i, types[i], tokens[i]);
        return (0);
	}
}
/*
        if (bs_position(tokens) == 0)
        {
            ft_error("This Shell does not support unspecified special characters \"\\\"", 0);
            return (1);
        }    
*/
void	extract_tokens(char **commands)
{
	int			i;
	int			nb;
	t_tokens	*tok;
    int         error_bs;

	i = 0;
    error_bs = 0;
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
		error_bs = print_types(tok[i].type, tok[i].nb, tok[i].tokens);
	}

    /* if (error_bs = 0)  */
	/* start_execution(); */

    i = -1;
	while (++i < nb)
	{
		free_toks(tok[i]);
		free(tok[i].type);
		tok[i].type = NULL;
	}
	// char *str="";
	free(tok);
}
