/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:01:07 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/18 07:47:49 by abelarif         ###   ########.fr       */
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

void        to_execution(t_tokens *tokens, int nb)
{
    char        **paths;
    int         i;

    i = -1;
    paths = get_paths();
    
    while (++i < nb)
    {
        tokens[i].exec_path = get_exec_path(tokens[i], paths);
        printf("NB PIPES : %d\n", tokens[i].pipe);
        printf("EXEC_PATH : [%s]\n", tokens[i].exec_path);
    }
    printf("Start execution : \n**********************************************\n");
    to_execution2(tokens);
    free_paths(paths);
}
