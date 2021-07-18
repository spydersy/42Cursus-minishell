/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:47:59 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/18 09:17:37 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_empty(char *str)
{
    int     i;

    i = -1;
    while (str[++i])
    {
        if (str[i] != ' ' && str[i] != '\t')
            return (0);
    }
    return (1);
}

int is_arg(int type)
{
    if (type == ARG || type == -ARG)
        return (1);
    return (0);
}

int is_cmd(int type)
{
    if (type == CMD || type == -CMD)
        return (1);
    return (0);
}

int is_redirection(int type)
{
    if (type == REDI0 || type == -REDI0)
        return (1);
    if (type == REDI1 || type == -REDI1)
        return (1);
    if (type == REDO0 || type == -REDO0)
        return (1);
    if (type == REDO1 || type == -REDO1)
        return (1);
    return (0);
}

int redirection_grammar(t_tokens *tokens)
{
    int     i;
    int     j;

    i = -1;
    while (++i < tokens->pipe)
    {
        j = -1;
        while (tokens[i].tokens[++j])
        {
            if (is_redirection(tokens[i].type[j]) != 0)
            {
                if (tokens[i].tokens[j + 1])
                {
                    if (!(tokens[i].type[j + 1] == FILE
                        || tokens[i].type[j + 1] == -FILE))
                        {
                            ft_error("No redirection File", 0);
                            return (0);
                        }
                }
                else
                {
                    ft_error("No redirection File", 0);
                    return (0);
                }
            }
        }
    }
    return (1);
}

int no_command(t_tokens *tokens)
{
    int     i;
    int     j;
    int     command;

    i = -1;
    while (++i < tokens->pipe)
    {
        j = -1;
        command = 0;
        while (tokens[i].tokens[++j])
        {
            if (tokens[i].type[j] == CMD || tokens[i].type[j] == -CMD)
            {
                command = 1;
                break;
            }
        }
        if (command == 0)
        {
            ft_error("No command", 0);
            return (1);
        }
    }
    return (0);
}

int grammar_checker(char **commands, t_tokens *tokens)
{
    int     i;

    i = -1;
    while (commands[++i])
    {
        if (is_empty(commands[i]) == 1)
        {
            ft_error("syntax error near unexpected token `|'", 0);
            return (0);
        }
    }
    i = -1;
    if (redirection_grammar(tokens) == 0)
    {
        return (0);
    }
    if (no_command(tokens) == 1)
        return (0);
    return (1);
}