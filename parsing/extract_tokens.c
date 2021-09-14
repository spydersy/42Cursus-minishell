/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:42:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/14 17:05:15 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	print_types(int *types, int nb, char **tokens)
{
	int		i;

	i = -1;
	while (++i < nb)
	{
		if (types[i] == CMD || types[i] == -CMD)
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
		else if (types[i] == HEREDOC || types[i] == -HEREDOC)
			printf("type[%d] , %d [%s]: [HEREDOC]\n", i, types[i], tokens[i]);
		else if (types[i] == EOFHEREDOC || types[i] == -EOFHEREDOC)
			printf("type[%d] , %d [%s]: [EOF]\n", i, types[i], tokens[i]);
		else
			printf("type[%d] , %d [%s]: [RANDOM]\n", i, types[i], tokens[i]);
	}
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

void    print_toks(char **str, int nb)
{
    int i;

    i = -1;
    while (str[++i])
    {
        printf("TOOOOOK [%d]: [%s]\n", nb, str[i]);
    }
}

void	extract_tokens(char **commands)
{
	int			i;
	int			nb;
	t_tokens	*tok;
    int         bs;

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
        printf("repeat : %d\n", i);
		tok[i].pipe = nb;
		tok[i].nb = count_tokens(commands[i]);
		tok[i].tokens = split_tok(commands[i], tok[i].nb);
		tok[i].type = set_tok_types(tok[i]);
		tok[i] = replace_dollar(tok + i); //WARNING PROTECTED TYPE
        print_toks(tok[i].tokens, 0);
		print_types(tok[i].type, tok[i].nb, tok[i].tokens);
	}
    i = 0;
    bs = bs_position(commands);

    if (bs == 0)
    {
        ft_error("This Shell does not support unspecified special characters \"\\\"", 0);
    }
    if (grammar_checker(commands, tok) == 1)
    {
        expand_quotes_dollar(tok);
    }
    i = -1;
	while (++i < nb)
	{
		free_toks(tok[i]);
		free(tok[i].type);
		tok[i].type = NULL;
	}
	free(tok);
}
