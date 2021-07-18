/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:41:21 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/11 17:03:52 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	minishell(argc, argv, envp);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 12:15:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/16 12:23:42 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int		main()
{
	char	*args[] = {"addd.out", NULL};
    char    *buffer;

	execve(args[1], args, NULL);
    perror(buffer);
	printf("FATAL\n");
	return (0);
}

/*
int main()
{
    int             ret;
    struct stat     statbuf;

    ret = stat("main.c", &statbuf);
    printf("%u\n", statbuf.st_mode);
    printf("ret : %d\n", ret);
    return (0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:09:10 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/11 17:05:12 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal_view(void)
{
	static int	first_time = 1;

	while (1)
	{
		signal(SIGINT, prompt);
		if (first_time)
		{
			clear_window();
			first_time = 0;
		}
		prompt(0);
		extract_semicolon_line(read_line());
	}	
}

void	free_env(void)
{
	int		i;

	i = -1;
	while (g_env.env[++i])
	{
		free(g_env.env[i]);
		free(g_env.sorted[i]);
		g_env.env[i] = NULL;
		g_env.sorted[i] = NULL;
	}
	free(g_env.env);
	free(g_env.sorted);
	g_env.env = NULL;
	g_env.sorted = NULL;
}

void	minishell(int argc, char *argv[], char *envp[])
{	
	if (argv[1] != NULL || argc != 1)
	{
		ft_error("Arguments", 1);
	}
	init_env(envp);
	terminal_view();
	free_env();
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 14:36:48 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 17:51:35 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void        exec_cd(char *path)
{
    int     ret;
    char    *old_pwd;
    char    *new_pwd;

    old_pwd = builtin_pwd(1);
    ret = chdir(path);
    if (ret == 0)
    {
        new_pwd = builtin_pwd(1);
        /*
        set_env("OLDPWD=", old_pwd);
        set_env("PWD=", new_pwd);
        */
    }
}

void        builtin_cd(char **path)
{
    int     i;

    i = 0;
    while (path[i])
    {
        i++;
    }
    if (i == 1)
    {
        exec_cd(path[0]);
    }
    ft_error(" cd: too many arguments", 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 16:18:08 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 16:22:46 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void        builtin_export(char **args)
{
    int     c;

    c = 0;
    while (args[c])
    {
        c++;
    
    }
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 12:49:06 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 14:48:26 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char        *builtin_pwd(int descriptor)
{
    char        *buffer;
    size_t      size;

    size = 10000;
    buffer = malloc(sizeof(char) * size);
    if (buffer == NULL)
        ft_error("MALLOC", 1);
    buffer = getcwd(buffer, size);
    if (descriptor == 1)
        return (buffer);
    else
    {
        ft_putendl_fd(buffer, STDOUT);
        free(buffer);
        buffer = NULL;
    }
    return (buffer);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execution2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 12:40:43 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:11:42 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void    count_redirections(t_tokens tokens, int type, int **arr_fds)
// {
//     int     i;
//     int     c;


//     c = 0;
//     i = -1;
//     while (++i < tokens.nb)
//     {
//         if (tokens.type[i] == type || tokens.type[i] == -type)
//             c++;
//     }
//     *arr_fds = malloc(sizeof(int) * (c + 1));
//     if (*arr_fds == NULL)
//         ft_error("MALLOC", 1);
//     *arr_fds[0] = c;
//     i = -1;
//     c = 0;
//     while (++i < tokens.nb)
//     {
//         if (tokens.type[i] == type || tokens.type[i] == -type)
//             *arr_fds[++c] = open(tokens.tokens[i + 1], O_RDONLY);
//     }
// }

// void    redirections_handler(int index, t_tokens *tokens)
// {
//     int     i;
//     // int     c;
//     int     *infile;
//     // int     *outfile;

//     i = -1;
//     infile = NULL;
//     count_redirections(tokens[index], REDI0, &infile);
//     while (++i < infile[0])
//     {
//         printf("infile fd[%d] = %d\n", i - 1, i + 1);
//     }
// }

// void    child_process(t_tokens *tokens, int *pipes)
// {
//     int     i;
//     pid_t   pid;

//     i = -1;
//     pipes = NULL;
//     while (++i < tokens->pipe)
//     {
//         printf("Child %d : |||||||||||||||||||||||||||||\n", i);
//         pid  = fork();
//         if (pid == -1)
//             ft_error("FORK", 1);
//         if (pid == 0) //child process
//         {
//             //  child_process
//             //  redirectoin priority (IO) is for files redirections not pipes;
//             //  About INPUT FILE  :  IF infile exist we must duplicate STDIN WITH FILE_FD
//             //                       ELSE we must duplicate STDIN WITH PIPE_IN
//             //  About OUTPUT FILE :  IF outfile exist we must create it & duplicate STDOUT WITH FILE_FD
//             //                       ELSE we must duplicate STDOUT WITH PIPE_OUT
//             redirections_handler(i, tokens);
//         }
//     }
//     // while (++i < (tokens->pipe - 1) * 2)
//     // {
//         // printf("PIPES FD : %d\n", pipes[i]);
//     // }
// }

int     to_execution2(t_tokens *tokens)
{
    int     i;
    int     pipes[(tokens->pipe - 1) * 2];

    i = -1;
    if (tokens->pipe == 1)
    {
        //exe_one_command();
    }
    else
    {
        while (++i < tokens->pipe - 1)
        {
            if (pipe(pipes + 2 * i) == -1)
                ft_error("PIPES", 1);
        }
        // child_process(tokens, pipes);
    }

    return (0);
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:01:07 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/18 10:31:44 by abelarif         ###   ########.fr       */
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

t_execution *expand_tokens(t_tokens *tokens, int nb)
{
    int             i;
    t_execution     *exec;
    char            **paths;

    i = -1;
    paths = get_paths();
    exec = malloc(sizeof(t_execution) * nb);
    if (exec == NULL)
        ft_error("MALLOC", 1);
    while (++i < nb)
    {
        exec[i].exec_path = get_exec_path(tokens[i], paths);
        exec[i].args = get_args(tokens[i]);
        // exec[i].redirections = get_redirections(tokens[i]);
    }
    free_paths(paths);
    return (exec);
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

    i = -1;
    while (str[++i])
    {
        if (str[i] == '$')
            return (1);
    }
    return (0);
}

void        expand_args(t_execution *exec, int nb)
{
    int     i;
    int     j;

    i = -1;
    while (++i < nb)
    {
        j = 0;
        while (exec[i].args[++j])
        {
            if (exec[i].args[j][0] == '\"' && dollar_is_presennt(exec[i].args[j]))
            {
                
            }
        }
    }
}

void        to_execution(t_tokens *tokens, int nb)
{
    t_execution     *exec;
    int             i;

    i = -1;
    exec = expand_tokens(tokens, nb);
    expand_args(exec);
    while (++i < nb)
    {
    printf("**********************************************\n");
            printf("exec_paths : [%s]\n",exec[i].exec_path);
            print_args(exec[i].args);
    printf("----------------------------------------------\n\n");
    }
    // while (++i < nb)
    // {
        // tokens[i].exec_path = get_exec_path(tokens[i], paths);
        // printf("NB PIPES : %d\n", tokens[i].pipe);
        // printf("EXEC_PATH : [%s]\n", tokens[i].exec_path);
    // }
    // to_execution2(tokens);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:09:37 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		get_rest(char *buf, char *save)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!buf)
		return ;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	while (buf[i])
		save[j++] = buf[i++];
	save[j] = '\0';
}

static void		get_line(char **line, char *rest)
{
	int			i;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	*line = ft_substr(rest, 0, i);
}

static int		read_to_buf(int fd, char **line, int *ret)
{
	char	*tmp;
	char	*buf;

	*ret = 1;
	while (ft_strchr(*line, '\n') == NULL && *ret != 0)
	{
		if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		if ((*ret = read(fd, buf, BUFFER_SIZE)) < 0)
			return (-1);
		buf[*ret] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
		free(buf);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	rest[1025][BUFFER_SIZE + 1] = {""};
	int			ret;
	char		*tmp;
	char		*f;

	*line = NULL;
	if (read(fd, NULL, 0) < 0 || !line || BUFFER_SIZE < 0)
		return (-1);
	if (ft_strchr(rest[fd], '\n') != NULL)
	{
		get_line(line, rest[fd]);
		get_rest(rest[fd], rest[fd]);
		return (1);
	}
	else
		*line = ft_strdup(rest[fd]);
	if (read_to_buf(fd, line, &ret) == -1)
		return (-1);
	f = *line;
	tmp = ft_strdup(*line);
	free(f);
	get_rest(tmp, rest[fd]);
	get_line(line, tmp);
	free(tmp);
	return ((ret > 0) ? 1 : 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:08:43 by abelarif          #+#    #+#             */
/*   Updated: 2020/01/10 18:36:46 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:09:28 by abelarif          #+#    #+#             */
/*   Updated: 2020/01/10 18:37:09 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	if (s)
	{
		while (*s)
			ft_putchar_fd(*s++, fd);
		ft_putchar_fd('\n', fd);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:10:13 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:54:35 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	nb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -n;
	}
	if (nb <= 9)
	{
		ft_putchar_fd(nb + 48, fd);
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(nb % 10 + 48, fd);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:11:18 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:55:16 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:42:12 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:51:20 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	len_word(const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i++])
		len++;
	return (len);
}

static	size_t	count_word(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (count);
}

void	*free_split(char **split, int k)
{
	while (k >= 0)
	{
		free(split[k]);
		k--;
	}
	free(split);
	split = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**split;

	i = 0;
	k = 0;
	split = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!s || split == NULL)
		return (NULL);
	while (i < count_word(s, c))
	{
		split[i] = (char *)malloc(sizeof(char) * (len_word(&s[k], c) + 1));
		if (split[i] == NULL)
			return ((free_split(split, k - 1)));
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k])
			split[i][j++] = s[k++];
		split[i][j] = '\0';
		i++;
	}
	split[i] = NULL;
	return (split);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:13:25 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:49:18 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:14:25 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:48:53 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	int		len;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	len++;
	s = malloc(len * sizeof(char));
	if (s == 0)
		return (0);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	s[i] = '\0';
	return (s);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:17:14 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:48:23 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		lens1;
	int		lens2;
	char	*p;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	p = malloc((lens1 + lens2 + 1) * sizeof(char));
	if (p == NULL)
		return (0);
	i = -1;
	while (++i < lens1)
		p[i] = s1[i];
	j = 0;
	while (i < (lens1 + lens2))
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:07:23 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/07/17 18:47:44 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:25:07 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:47:28 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:26:32 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:46:55 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:35:15 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:45:32 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		sub = (char *)malloc(sizeof(char));
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

char	*ft_subtoken(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	int				i;

	i = 0;
	sub = malloc(sizeof(char) * (len - start + 1));
	if (sub == NULL)
		ft_error("malloc", 1);
	while (start < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:09:37 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		get_rest(char *buf, char *save)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!buf)
		return ;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	while (buf[i])
		save[j++] = buf[i++];
	save[j] = '\0';
}

static void		get_line(char **line, char *rest)
{
	int			i;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	*line = ft_substr(rest, 0, i);
}

static int		read_to_buf(int fd, char **line, int *ret)
{
	char	*tmp;
	char	*buf;

	*ret = 1;
	while (ft_strchr(*line, '\n') == NULL && *ret != 0)
	{
		if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		if ((*ret = read(fd, buf, BUFFER_SIZE)) < 0)
			return (-1);
		buf[*ret] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
		free(buf);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	rest[1025][BUFFER_SIZE + 1] = {""};
	int			ret;
	char		*tmp;
	char		*f;

	*line = NULL;
	if (read(fd, NULL, 0) < 0 || !line || BUFFER_SIZE < 0)
		return (-1);
	if (ft_strchr(rest[fd], '\n') != NULL)
	{
		get_line(line, rest[fd]);
		get_rest(rest[fd], rest[fd]);
		return (1);
	}
	else
		*line = ft_strdup(rest[fd]);
	if (read_to_buf(fd, line, &ret) == -1)
		return (-1);
	f = *line;
	tmp = ft_strdup(*line);
	free(f);
	get_rest(tmp, rest[fd]);
	get_line(line, tmp);
	free(tmp);
	return ((ret > 0) ? 1 : 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:21:39 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_window(void)
{
	write(1, "\e[1;1H\e[2J", ft_strlen("\e[1;1H\e[2J"));
}

char	*read_line(void)
{
	char	*line;

	if (get_next_line(0, &line) < 0)
		ft_error("Get Next Line", 1);
    return (line);
}

void	prompt(int sig)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 500);
	if (buffer == NULL)
		ft_error("MALLOC", 1);
	buffer = getcwd(buffer, 500);
	if (sig == 2)
		write(1, "\n", 1);	
	ft_putstr_fd(KGRN, 1);
	ft_putstr_fd("MINISHELL (", 1);
	ft_putstr_fd(KBLU, 1);
	ft_putstr_fd(buffer, 1);
	ft_putstr_fd(KGRN, 1);
	ft_putstr_fd(") > ", 1);
	ft_putstr_fd(KWHT, 1);
	free(buffer);
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:28:10 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 09:13:49 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	extract_pipe_line(char *line)
{
	int					i;
	t_separator			c_separator;
	int					error;

	i = -1;
	error = 0;
	c_separator = get_separator_index(line, '|');
	if (c_separator.nb_separator == 0)
		c_separator.content = ft_split(line, '\0');
	else
		c_separator.content = splitSep(line, c_separator.separator_index, c_separator.nb_separator);
	free(c_separator.separator_index);
	c_separator.separator_index = NULL;
	while (c_separator.content[++i])
	{
		if (c_separator.content[i][0] == '|' || c_separator.content[i][0] == ';')
			error = 1;
		printf("     command %d : [%s]\n", i, c_separator.content[i]);
		printf("\n");
	}
	if (error == 0)
		extract_tokens(c_separator.content);
	i = -1;
	while (c_separator.content[++i])
	{
		free(c_separator.content[i]);
		c_separator.content[i] = NULL;
	}
	free(c_separator.content);
	c_separator.content = NULL;
}

void	extract_semicolon_line(char *line)
{
	int				i;
	int				flag;
	t_separator		cl_separator;

	i = -1;
	flag = 0;
	if (ft_strlen(line) == 0)
	{
		free(line);
		line = NULL;
		return ;
	}
	cl_separator = get_separator_index(line, ';');
	if (cl_separator.nb_separator == 0)
    {
		cl_separator.content = ft_split(line, '\0');
	    extract_pipe_line(cl_separator.content[0]);
	    free(cl_separator.content[0]);
	    cl_separator.content[0] = NULL;
    	free(cl_separator.content);
    }
    else
	{
        ft_error("This Shell does not support unspecified special characters \";\"", 0);
    }    
	free(line);
	free(cl_separator.separator_index);
	cl_separator.separator_index = NULL;
	line = NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:42:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/18 09:49:02 by abelarif         ###   ########.fr       */
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
		else
			printf("type[%d] , %d [%s]: [random]\n", i, types[i], tokens[i]);
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
		tok[i].pipe = nb;
		tok[i].nb = count_tokens(commands[i]);
		tok[i].tokens = split_tok(commands[i], tok[i].nb);
		tok[i].type = set_tok_types(tok[i]);
		tok[i] = replace_dollar(tok + i); //WARNING PROTECTED TYPE
		print_types(tok[i].type, tok[i].nb, tok[i].tokens);
	}
    bs = bs_position(commands);
    if (bs == 0)
    {
        ft_error("This Shell does not support unspecified special characters \"\\\"", 0);
    }
    if (grammar_checker(commands, tok) == 1)
    {
        to_execution(tok, nb);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:18:54 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/12 13:10:00 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_search(char *str, int index)
{
    int         i;
    int         lensrc;
    char        *env;

    env = NULL;
    i = -1;

	if (index != 0)
		index = 1;
    lensrc = ft_strlen(str + index);
    while (g_env.sorted[++i])
    {
        if (ft_strncmp(str + 1 + index, g_env.sorted[i], lensrc - 1) == 0
        && g_env.sorted[i][lensrc - 1] == '=') //edit
        {
            env = ft_substr(g_env.sorted[i], lensrc, ft_strlen(g_env.sorted[i]) - lensrc  + 2);
			free(str);
			str = NULL;
			return (env);
        }
    }
	free(str);
	str = NULL;
    return (ft_strdup(""));
}

void	dollar_handling(char **tok, int index)
{
	char		*str;

	str = ft_strdup(*tok);
	free(*tok);
	*tok = NULL;
    *tok = env_search(str, index);
	if (*tok == NULL)
		ft_error("tok", 1);
}

int	count(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	free_dollar(char **old, char **content)
{
	int		i;

	i = -1;
	while (old[++i])
	{
		free(old[i]);
		old[i] = NULL;
	}
	i = -1;
	while (content[++i])
	{
		free(content[i]);
		content[i] = NULL;
	}
	free(old);
	free(content);
	old = NULL;
	content = NULL;
}

char	**split_dollar_signe(char **old, int index)
{
	int		i;
	int		c;
	char	**content;
	char	**new;

	i = -1;
	content = ft_split(old[index], ' ');
	new = malloc(sizeof(char*) * (count(old) + count(content)));
	while (++i < index)
		new[i] = ft_strdup(old[i]);
	c = -1;
	while (content[++c])
	{
		new[i] = ft_strdup(content[c]);
		i++;
	}
	c = index;
	while (old[++c])
	{
		new[i] = ft_strdup(old[c]);
		i++;
	}
	new[i] = NULL;
	free_dollar(old, content);
	return (new);
}

void	set_types(t_tokens *tok, int oldlen, int newlen, int index)
{
	int		i;
	int		c;
	int		*newtype;

	i = -1;
	newtype = malloc(sizeof(int) * newlen);
	if (newtype == NULL)
	{
		ft_error("set types", 1);
	}
	while (++i < index)
	{
		newtype[i] =  tok->type[i];
	}
	c = -1;
	while (++c < newlen - oldlen + 1)
	{
		if (c == 0)
			newtype[i] = PROTECTED0;
		else
			newtype[i] = PROTECTED1;
		i++;
	}
	c = index;
	while (++c < oldlen)
	{
		newtype[i] = tok->type[c];
		i++;
	}
	free(tok->type);
	tok->type = NULL;
	tok->type = newtype;
}

t_tokens	replace_dollar(t_tokens *tok)
{
    int         i;
    int         presence;
    int         oldlen;
    int         newlen;

    presence = 1;
    oldlen = count(tok->tokens);
    newlen = oldlen;
    i = -1;
    while (presence)
    {
        presence = 0;
        while (tok->tokens[++i])
        {
            if (tok->tokens[i][1] == '$' || (i == 0 && tok->tokens[i][0] == '$'))
            {
				dollar_handling(&(tok->tokens[i]), i);
				tok->tokens = split_dollar_signe(tok->tokens, i);
				presence = 1;
				newlen = count(tok->tokens);
				if (oldlen != newlen)
					set_types(tok,  oldlen, newlen, i);
				else if (tok->type[i] < 0)
					tok->type[i] = -PROTECTED0;
				else
					tok->type[i] = PROTECTED0;
				i += newlen - oldlen;
				oldlen = newlen;
				break ;
            }
        }
		tok->nb = i;
    }
    return (*tok);
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:16:03 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 10:14:54 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int						skip_spaces(char *line, int index)
{
	while (line[index])
	{
		if (line[index] == ' ' || line[index] == '\t')
			index++;
		else
			return (index);
	}
	return (index);
}

int						token_dollar(char *line, int index)
{
	if (line[index + 1] && line[index + 1] == '$')
        return (index + 2);
    index++;
    while (line[index])
    {
        if (line[index] == '$' || line[index] == ' ' || line[index] == '\t'
            || line[index] == '\'' || line[index] == '\"' || line[index] == '>'
            || line[index] == '<' || line[index] == '\0')
            return (index);
        else
            index++;
    }
    return (index);
}

int						token_word(char *line, int index)
{
	while (line[index])
    {
        if (line[index] == '$' || line[index] == ' ' || line[index] == '\t'
			|| line[index] == '>'
            || line[index] == '<' || line[index] == '\0')
                return (index);
        else if ((line[index] == '\'' || line[index] == '\"') && (count_bs(line, index) % 2 == 0))
			return (index);
		else
            index++;
    }
    return (index);
}

int						token_quotes(char *line, int index)
{
    int         i;

    i = index + 1;
	while (line[i])
    {
		if (line[i] == line[index] && line[index] == '\'')
            return (i + 1);
        if (line[i] == line[index] && (count_bs(line, i) % 2 == 0))
            return (i + 1);
		i++;
    }
    return (-1);
}

int						token_redir(char *line, int index)
{
	int					i;

	i = index;
	while (line[i])
	{
		if (line[i] == line[index])
		{
			i++;
		}
		else
			return (i);
	}
	return (i);
}

int						get_end(char *line, int index)
{

	if ((line[index] == '>' || line[index] == '<')
	&& count_bs(line, index) % 2 == 0)
	{
		index = token_redir(line, index);
	}
	else if (line[index] == '$'
	&& count_bs(line, index) % 2 == 0)
	{
		index = token_dollar(line, index);
	}
	else if (line[index] == '\'' || line[index] == '\"')
	{
		index = token_quotes(line, index);
        if (index == -1)
            ft_error("This Shell does not support unclosed quotes.", 0);
	}
	else
	{
		index = token_word(line, index);
	}
	return (index);
}

int						count_tokens(char *line)
{
	int		i;
	int		c;

	c = 0;
	i = 0;
	while (line[i])
	{
		if (line[i])
		{
			i = skip_spaces(line, i);
		}
		if (line[i])
		{
			i = get_end(line , i);
			if (i == -1)
				return (c);
			c++;
		}
		else
			return (c);
	}
    return (c);
}

char					*get_token(char *line, int flag)
{
	static int 			start = 0;
	char				*token;
	int					end = 0;
	int					bef;

	token = NULL;
	bef = 1;
	if (flag == 0)
		start = 0;
	if (start == 0)
		bef = 0;
	while (line[start])
	{
		start = skip_spaces(line, start);
		if (line[start])
		{
			end = get_end(line, start);
			if (end != -1)
				token = ft_subtoken(line, start - bef, end);
			start = end;
			return (token);
		}
	}
	return (token);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:21:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 10:05:59 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_bs(char *line, int index)
{
	int	c;

	c = 0;
	if (index == 0)
		return (0);
	while (index-- >= 0)
	{
		if (index >= 0 && line[index] == '\\')
			c++;
		else
			break ;
	}
	return (c);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:36:06 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 10:04:26 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_env(void)
{
	int		i;
	int		repeat;
	char	*tmp;

	tmp = NULL;
	repeat = 1;
	while (repeat)
	{
		i = -1;
		repeat = 0;
		while (g_env.sorted[++i])
		{
			if (g_env.sorted[i] && g_env.sorted[i + 1]
				&& ft_strncmp(g_env.sorted[i], g_env.sorted[i + 1],
					max_of(ft_strlen(g_env.sorted[i]),
						ft_strlen(g_env.sorted[i + 1]))) > 0)
			{
				tmp = g_env.sorted[i];
				g_env.sorted[i] = g_env.sorted[i + 1];
				g_env.sorted[i + 1] = tmp;
				repeat = 1;
			}
		}
	}
}

void	init_env(char **env)
{
	int		c;

	c = 0;
	while (env[c])
		c++;
	g_env.env = malloc(sizeof(char *) * (c + 1));
	g_env.sorted = malloc(sizeof(char *) * (c + 1));
	if (g_env.env == NULL || g_env.sorted == NULL)
		ft_error("malloc", 1);
	g_env.size = c;
	c = -1;
	while (env[++c])
	{
		g_env.env[c] = ft_strdup(env[c]);
		g_env.sorted[c] = ft_strdup(env[c]);
		if (g_env.env[c] == NULL || g_env.sorted[c] == NULL)
			ft_error("malloc", 1);
	}
	g_env.env[c] = NULL;
	g_env.sorted[c] = NULL;
	sort_env();
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:08:49 by abelarif          #+#    #+#             */
/*   Updated: 2021/05/11 22:24:32 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error(char *description, int exitstat)
{
	/* FREE */
	write(2, KRED, ft_strlen(KRED));
	write(2, "Error\n", 6);
	if (description)
	{
		write(2, description, ft_strlen(description));
	}
	else
	{
		/* GET DESCRIPTION USING ERRNO STRERROR */
	}
	write(2, "\n", 1);
	write(1, KWHT, ft_strlen(KWHT));
	if (exitstat == 1)
		exit(EXIT_FAILURE);
	return (errno);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:47:59 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/18 09:52:16 by abelarif         ###   ########.fr       */
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

int is_protected(int type)
{
    if (type == PROTECTED0 || type == -PROTECTED0)
        return (1);
    if (type == PROTECTED1 || type == -PROTECTED1)
        return (1);
    return (0);
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
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:34:22 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/18 07:03:23 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_quote				init_quote(void)
{
	t_quote		quote;

	quote.s_quote = false;
	quote.d_quote = false;
	return (quote);
}

t_quote				set_quote_value(char quote_type, t_quote to_quote)
{
	t_quote		quote;

	quote.d_quote = to_quote.d_quote;
	quote.s_quote = to_quote.s_quote;
	if(to_quote.d_quote == false && to_quote.s_quote == false)
	{
		if (quote_type == 39)
			quote.s_quote = true;
		else
			quote.d_quote = true;
	}
	else if ((to_quote.s_quote == true) && (quote_type == 39))
			quote.s_quote = false;
	else if ((to_quote.d_quote == true) && (quote_type == 34))
			quote.d_quote = false;
	return (quote);
}

int					count_separators(char *line, char separator)
{
	int				i;
	t_quote			quote;
	int				c;

	c = 0;
	i = -1;
	quote = init_quote();
	 
	while (line[++i])
	{
		if ((line[i] == 39 || line[i] == 34))
			if (count_bs(line, i) % 2 == 0)
				quote = set_quote_value(line[i], quote);
		if (separator == ';' && line[i] == ';' && line[i + 1] == ';')
			ft_error("syntax error near unexpected token `;;'", 0);
		else if (separator == '|' && line[i] == '|' && line[i + 1] == '|')
			ft_error("syntax error near unexpected token `|'", 0);
		else if (line[i] == separator)
			if (count_bs(line, i) % 2 == 0)
				if (!quote.s_quote && !quote.d_quote)
				c++;
	}
	return (c);
}

t_separator			get_separator_index(char *line, char separator_type)
{
	t_quote			quote;
	int             i;
	int				c;
	t_separator		separator;

	i = -1;
	c = -1;
	quote = init_quote();
	separator.separator_index = NULL;
    separator.nb_separator = count_separators(line, separator_type);
	separator.separator_index = malloc(separator.nb_separator * sizeof(int));
	if (separator.separator_index == NULL)
		ft_error(NULL, 1);
	while (line[++i])
	{
		if ((line[i] == 39 || line[i] == 34) && (count_bs(line, i) % 2 == 0))
			quote = set_quote_value(line[i], quote);
		else if (line[i] == separator_type && (count_bs(line, i) % 2 == 0))
			if (!quote.s_quote && !quote.d_quote && c + 1 < separator.nb_separator)
				separator.separator_index[++c] = i;
	}
	return (separator);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_of.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:04:08 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 10:22:26 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	max_of(int i, int j)
{
	if (i < j)
		return (j);
	else
		return (i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:38:55 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 16:16:42 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void        replace_value(int index, char *new_value, int var_len, char **arr)
{
    int     i;
    int     j;
    char    *new_env;
    int     new_len;

    i = -1;
    new_len = ft_strlen(new_value);
    new_env = malloc(sizeof(char) * (new_len + var_len + 1));
    if (new_env == NULL)
        ft_error("MALLOC", 1);
    while (++i < var_len)
    {
        new_env[i] = arr[index][i];
    }
    j = -1;
    while (++j < new_len)
    {
        new_env[i] = new_value[j];
        i++;
    }
    new_env[i] = '\0';
    free(arr[index]);
    arr[index] = new_env;
}

void        set_env(char *env, char *new_value)
{
    int     i;
    size_t  len;

    i = -1;
    len = ft_strlen(env);
    while (g_env.env[++i])
    {
        if (ft_strncmp(env, g_env.env[i], len) == 0)
        {
            replace_value(i, new_value, len, g_env.env);
            break ;
        }
    }
    i = -1;
    while (g_env.sorted[++i])
    {
        if (ft_strncmp(env, g_env.sorted[i], len) == 0)
        {
            replace_value(i, new_value, len, g_env.sorted);
            break ;
        }
    }
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:03:02 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**splitSep(char *line, int *sepIndex, int nbSep)
{
	int		i;
	char	**content;
	int		index;

	index = 0;
	i = -1;
	if ((content = malloc(sizeof(char*) * (nbSep + 2))) == NULL)
		return (NULL);
	while (++i < nbSep + 1)
	{
		if (i == nbSep)
		{
			index = ((i == 0) ? (sepIndex[nbSep - 1])
								: (sepIndex[nbSep - 1] + 1));
			content[i] = ft_substr(line, index, ft_strlen(line) - index);
			break;
		}
		content[i] = ft_substr(line, index, sepIndex[i] - index);
		if (content[i] == NULL)
			return (NULL);
		index = sepIndex[i] + 1;
	}
	content[nbSep + 1] = NULL;
	return (content);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:06:45 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 10:08:38 by abelarif         ###   ########.fr       */
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
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:41:44 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/18 09:51:17 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/errno.h>
# include <sys/types.h>
# include "./libft/libft.h"
# include "./line_reader/get_next_line.h"

		/*	COLORS		*/
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

# define STDIN  0
# define STDOUT 1
# define STDERR 2


/*	>				*/
/*	>>				*/
/*	<				*/
/*	<<				*/





# define CMD        9001 /*	arguments		*/
# define ARG        9002 
# define REDO0		9003 
# define REDO1		9004 
# define REDI0		9005 
# define REDI1		9006 
# define FILE		9007 /*	file			*/
# define ERROR		9008 /*	error			*/
# define PROTECTED0	9009 /*	protected arg	*/
# define PROTECTED1	9010 /*	protected arg	*/
# define SKIPED		9011 /*	skiped tok		*/
typedef struct s_quote
{
	bool				s_quote;
	bool				d_quote;
}						t_quote;

typedef struct s_env
{
	char				**env;
	char				**sorted;
	char				**history;
	int					history_size;
	int					size;
}						t_env;

typedef struct s_tokens
{
	int					nb;
	int					pipe;
	int					*type;
	char				**tokens;
	char				*exec_path;
}						t_tokens;

typedef struct s_separator
{
	int					*separator_index;
	int					nb_separator;
	char				**content;
}						t_separator;

typedef struct s_execution
{
    int                 nb_commands;
    char                **args;
    char                **redirections;
    char                *exec_path;
}                       t_execution;


t_env					g_env;

int                     is_arg(int type);
int                     is_cmd(int type);
int						max_of(int i, int j);
int                     is_protected(int type);
int						count_bslash(char *line);
int						count_tokens(char *line);
int						bs_position(char **tokens);
int						*set_tok_types(t_tokens tok);
int						to_execution2(t_tokens *tokens);
int						count_bs(char *line, int index);
int						*get_bslash_index(char *line, int nb);
int						ft_error(char *description, int exitstat);
int                     grammar_checker(char **commands, t_tokens *tokens);

void					prompt(int sig);
void					to_execution(t_tokens *tokens, int nb);
void					free_toks(t_tokens tok);
void					init_env(char **env);
void					clear_window(void);
void					extract_semicolon_line(char *line);
void					minishell(int argc, char *argv[], char *envp[]);
void					extract_tokens(char **commands);
void					set_separator_type(int *type, char **toks);

char					*read_line(void);
char					*builtin_pwd(int descriptor);
char					**split_tok(char *line, int nb);
char					*get_token(char *line, int flag);
char					**splitSep(char *line, int *sepIndex, int nbSep);

t_tokens				replace_dollar(t_tokens *tok);
t_quote					init_quote(void);
t_quote					set_quote_value(char quote_type, t_quote to_quote);
t_separator				get_separator_index(char *line, char separator_type);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:10:00 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/02/22 16:26:25 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		get_next_line(int fd, char **line);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:53:10 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/17 18:46:08 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "../minishell.h"

int				ft_strncmp(const char *s1, const char *s2, size_t n);

char			*ft_strdup(const char *src);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_subtoken(char const *s, unsigned int start, size_t len);

void			ft_putnbr_fd(int nb, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char const *s, int fd);

size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:10:00 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/02/22 16:26:25 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		get_next_line(int fd, char **line);

#endif
