/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:01:07 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/07 09:51:56 by abelarif         ###   ########.fr       */
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
    int     count;

    i = -1;
    count = 0;
    while (str[++i])
    {
        if (str[i] == '$')
            count++;
    }
    return (count);
}

char    *ft_charjoin(char *str, char c)
{
    int     i;
    int     len;
    char    *ret;

    i = -1;
    len = ft_strlen(str) + 1;
    if (c != '\0')
        len++;
    ret = malloc(sizeof(char) * len);
    while (str[++i])
    {
        ret[i] = str[i];
    }
    if (c != '\0')
        ret[i++] = c;
    ret[i] = '\0';
    free(str);
    return (ret);
}

// char    dolla_handling(char *str, int index)
// {
//     int     i;
//     int     end;

//     i = index;
//     while (str[++i])
//     {
//         if (str[i] == ' ' || str[i] == '\t')
//             break ;
//     }
//................................ LAST MODIFICATION ..........
// }

// We will add DOLLAR HANDLING FUNCTION HERE IF IT NOT EXIST :) ...

char    *sub_dollar(char *str, int index)
{
    int     i;
    char    *tmp;

    i = index;
    while (str[++i])
    {
        if ((str[i] == ' ' || str[i] == '\t') && i == index + 1)
            return (ft_strdup("$"));
        else if ((str[i] == ' ' || str[i] == '\t'))
        {
            tmp = ft_substr(str, index, i - index);
            dollar_handling(&tmp, 0);
            return (tmp);
        }
    }
    if (str[i - 1] == '$')
        return (ft_strdup("$"));
    tmp = ft_substr(str, index, i - index);
    dollar_handling(&tmp, 0);
    return (tmp);
}

int dollar_len(char *str, int index)
{
    int i;

    i = index;
    while (str[++i])
    {
        if (str[i] == ' ' || str[i] == '\t')
            return (i - index);
    }
    return (i - index);
}

char    *expand_dollars(char *str)
{
    int     i;
    char    *content;
    char    *tmp;

    i = -1;
    content = ft_strdup("");
    while (str[++i])
    {
        if (str[i] != '$')
        {
            content = ft_charjoin(content, str[i]);
        }
        else
        {
            tmp = sub_dollar(str, i);
            content = ft_strjoin(content, tmp);
            i += dollar_len(str, i) - 1;
        }
    }
    return (content);
}

char *expand_quotes(char *content, int index)
{
    int     nb_dollars;
    char    *tmp;

    tmp = ft_substr(content, index + 1, ft_strlen(content) - 2 - index);
    nb_dollars = dollar_is_present(tmp);
    if (content[index] == '\"' && nb_dollars != 0)
    {
        tmp = expand_dollars(tmp);
    }
    return (tmp);
}

t_tokens    select_quotes(t_tokens tokens)
{
    int     i;
    int     dqIndex;

    i =-1;
    while (tokens.tokens[++i])
    {
        dqIndex = 0;
        if (i != 0)
            dqIndex++;
        if (tokens.tokens[i][dqIndex] == '\"'
            || tokens.tokens[i][dqIndex] == '\'')
        {
            tokens.tokens[i]
            = expand_quotes(tokens.tokens[i], dqIndex);
        }
    }
    return (tokens);
}

void        print_new(t_tokens tok)
{
    int     i;

    i = -1;
    while (++i < tok.nb)
    {
        printf("NEW TOKENS : [%s]\n", tok.tokens[i]);
    }
}

void        to_execution(t_tokens *tokens, int nb)
{
    if (nb){}

    int     i;
    int     pipes;

    i = -1;
    pipes = tokens[0].pipe;
    printf("LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n");
    while (++i < pipes)
    {
        tokens[i] = select_quotes(tokens[i]);
        print_new(tokens[i]);
    }
}
