/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:38:32 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/13 12:34:43 by abelarif         ###   ########.fr       */
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

int is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0)
    {
        printf("ALOOOOOOOOOOOOOOOOHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA            [%s]\n", cmd);
        return (1);
    }if (ft_strcmp(cmd, "cd") == 0)
        return (1);
    if (ft_strcmp(cmd, "pwd") == 0)
        return (1);
    if (ft_strcmp(cmd, "export") == 0)
        return (1);
    if (ft_strcmp(cmd, "unset") == 0)
        return (1);
    if (ft_strcmp(cmd, "env") == 0)
        return (1);
    if (ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
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
        if (token.type[i] == CMD || token.type[i] == -CMD)
            break ;
    if (is_builtin(token.tokens[i]) == 1)
    {
        free_paths(paths);
        return (ft_strdup("builtin"));
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
			free_paths(paths);
            return (ft_strdup(token.tokens[i] + index));
        }
    }
	if (paths[0] == NULL)
	{
		free_paths(paths);
		return (ft_strdup(""));free_paths(paths);
	}
    free_paths(paths);
	return (exec_path);
}

// char    *ft_replace(t_tokens token, int index)
// {
//     if (is_cmd(token.type[index]))
//     {
//         if (index == 0)
//             return (ft_strdup(token.tokens[index]));
//         else
//             return (ft_strdup(token.tokens[index] + 1));
//     }
//     else if (is_arg(token.type[index]))
//     {
//         return (ft_strdup(token.tokens[index] + 1));
//     }
//     if (is_protected(token.type[index]))
//     {
//         return (ft_strdup(token.tokens[index]));
//     }
//     return (NULL);
// }

// char    **get_args(t_tokens tokens)
// {
//     int     i;
//     int     c;
//     char    **args;

//     c = 0;
//     i = -1;
//     while (tokens.tokens[++i])
//     {
//         if (is_arg(tokens.type[i]) || is_cmd(tokens.type[i])
//             || is_protected(tokens.type[i]))
//             c++;
//     }
//     args = malloc(sizeof(char *) * (c + 1));
//     if (args == NULL)
//         ft_error("MALLOC", 1);
//     i = -1;
//     c = -1;
//     while (tokens.tokens[++i])
//     {
//         if (is_cmd(tokens.type[i]) || is_arg(tokens.type[i])
//             || is_protected(tokens.type[i]))
//             args[++c] = ft_replace(tokens, i);
//     }
//     args[c + 1] = NULL;
//     return (args);
// }
