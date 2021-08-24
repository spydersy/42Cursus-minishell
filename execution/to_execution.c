/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:01:07 by abelarif          #+#    #+#             */
/*   Updated: 2021/08/24 13:25:03 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_bs(char **paths)
{
	int		i;
	char	*tmp;

	i = -1;
	if (paths == NULL)
		return ;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
	}
}

char        **get_paths(void)
{
	int		i;
	int		cmp;
	char	**paths;

	i = -1;
	while (g_env.env[++i])
	{
		cmp = ft_strncmp(g_env.env[i], "PATH=", 5);
		if (cmp == 0)
			break ;
	}
	if (g_env.env[i] == NULL)
		return (ft_split("", '\0'));
	else
	{
		paths = ft_split(g_env.env[i] + 6, ':');
		if (paths == NULL)
			ft_error(NULL, 1);
        join_bs(paths);
		return (paths);
	}
}

void        free_paths(char **paths)
{
    int     i;

    i = -1;
    while (paths[++i])
    {
        free(paths[i]);
        paths[i] = NULL;
    }
    free(paths);
    paths = NULL;
}

char        *join_paths(t_tokens tokens, int index, char **paths)
{
    int     i;
    int     fd;
    char    *tmp;
    char    *cmd;

    i = -1;
    cmd = tokens.tokens[index];
    if (index != 0)
        cmd = tokens.tokens[index] + 1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		fd = open(tmp, O_RDONLY, 0666);
		if (fd < 0)
		{
			free(tmp);
			tmp = NULL;
		}
		else
		{
			close(fd);
			return (tmp);
		}
	}
    return (NULL);
}

char        *get_exec_path(t_tokens token, char **paths)
{
    int     i;
    int     fd;
    int     index;
    char    *exec_path;

    i = -1;
    index = 0;
    while (++i < token.nb)
    {
        if (token.type[i] == CMD || token.type[i] == -CMD)
            break ;
    }
    exec_path = join_paths(token, i, paths);
    if (exec_path == NULL)
    {
        if (i != 0)
            index++;
        fd = open(token.tokens[i] + index, O_RDONLY, 0666);
        if (fd > 0)
        {
            close(fd);
            return (token.tokens[i] + index);
        }
    }
    return (exec_path);
}

char    *ft_replace(t_tokens token, int index)
{
    if (is_cmd(token.type[index]))
    {
        if (index == 0)
            return (ft_strdup(token.tokens[index]));
        else
            return (ft_strdup(token.tokens[index] + 1));
    }
    else if (is_arg(token.type[index]))
    {
        return (ft_strdup(token.tokens[index] + 1));
    }
    if (is_protected(token.type[index]))
    {
        return (ft_strdup(token.tokens[index]));
    }
    return (NULL);
}

char    **get_args(t_tokens tokens)
{
    int     i;
    int     c;
    char    **args;

    c = 0;
    i = -1;
    while (tokens.tokens[++i])
    {
        if (is_arg(tokens.type[i]) || is_cmd(tokens.type[i])
            || is_protected(tokens.type[i]))
            c++;
    }
    args = malloc(sizeof(char *) * (c + 1));
    if (args == NULL)
        ft_error("MALLOC", 1);
    i = -1;
    c = -1;
    while (tokens.tokens[++i])
    {
        if (is_cmd(tokens.type[i]) || is_arg(tokens.type[i])
            || is_protected(tokens.type[i]))
            args[++c] = ft_replace(tokens, i);
    }
    args[c + 1] = NULL;
    return (args);
}

// char    **get_redirections(t_tokens token)
// {
    // int     i;
    // int     c;
    // char    **redirections;

    // i = -1;
    // c = 0;

    // while (token.tokens[++i])
    // {
        // if ()
        // {

        // }
    // }
// }

// t_execution *expand_tokens(t_tokens *tokens, int nb)
// {
    // int             i;
    // t_execution     *exec;
    // char            **paths;

    // i = -1;
    // paths = get_paths();
    // exec = malloc(sizeof(t_execution) * nb);
    // if (exec == NULL)
        // ft_error("MALLOC", 1);
    // while (++i < nb)
    // {
        // exec[i].exec_path = get_exec_path(tokens[i], paths);
        // exec[i].args = get_args(tokens[i]);
        // // exec[i].redirections = get_redirections(tokens[i]);
    // }
    // free_paths(paths);
    // return (exec);
// }

void        print_args(char **args)
{
    int     i;

    i = -1;
    while (args[++i])
    {
        printf("\targ[%d] : [%s]\n", i, args[i]);
    }
}

int         dollar_is_present(char *str)
{
    int     i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '$')
            return (1);
    }
    return (0);
}

void        to_execution(t_tokens *tokens, int nb)
{
    int i;

    i = -1;
    if (nb){}
    while (++i < tokens[0].pipe)
    {
        expand_double_quotes(tokens[i]);
    }
    // print_toks(tokens[i + 1].tokens, 12);
    // printf("NB : %d\n", tokens[i + 1].nb);
    // while (++i < nb)
    // {
    // printf("**********************************************\n");
            // printf("exec_paths : [%s]\n",exec[i].exec_path);
            // print_args(exec[i].args);
    // printf("----------------------------------------------\n\n");
    // }
}
