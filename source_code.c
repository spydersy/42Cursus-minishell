/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:41:21 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/16 17:28:11 by abelarif         ###   ########.fr       */
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
/*   buil_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 12:49:06 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/16 13:13:44 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void        buil_pwd(void)
// {
    
// }/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execution2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 12:40:43 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/16 17:21:08 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    child_process(t_tokens *tokens, int *pipes)
{
    int     i;
    pid_t   pid;

    i = -1;
    while (++i < tokens->pipe)
    {
        pid  = fork();
        if (pid == -1)
            ft_error("FORK", 1);
        if (pid == 0) //child process
        {
            
        }
    }
    // while (++i < (tokens->pipe - 1) * 2)
    // {
        // printf("PIPES FD : %d\n", pipes[i]);
    // }
}

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
        child_process(tokens, pipes);
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
/*   Updated: 2021/07/16 13:38:52 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:15:00 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:12:14 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int			i;
	int			res;
	long long	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13 && str[i]) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = 1 - 2 * (str[i++] == '-');
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (res < 0 && sign < 0)
			return (0);
		if (res < 0 && sign > 0)
			return (-1);
		res = (res * 10) + (str[i++] - '0');
	}
	return (res * sign);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:24:00 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:12:45 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	if (n)
		ft_memset(s, 0, n);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:04:04 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *ret;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	if (!(ret = malloc(count * size)))
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:46:14 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:13:53 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:25:31 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:17:42 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:55:56 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:18:17 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:40:50 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/12 23:12:29 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:08:25 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:48:39 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:43:38 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len(int n)
{
	int l;

	if (n >= 0)
		l = 1;
	else
		l = 2;
	while ((n /= 10) != 0)
		l++;
	return (l);
}

static void		ft_put_itoa(int n, char *ret)
{
	if ((n / 10) > 0)
	{
		ft_put_itoa(n / 10, ret - 1);
		*ret = (n % 10) + '0';
	}
	else
		*ret = n + '0';
}

char			*ft_itoa(int n)
{
	char	*ret;

	if (n == -2147483648)
	{
		if (!(ret = (char*)malloc(sizeof(char) * 12)))
			return (NULL);
		ft_strlcpy(ret, "-2147483648", 12);
		return (ret);
	}
	if (!(ret = (char*)malloc(sizeof(char) * (len(n) + 1))))
		return (NULL);
	*(ret + len(n)) = '\0';
	if (n < 0)
	{
		*ret = '-';
		n *= -1;
		ft_put_itoa(n, ret + len(n));
	}
	else
		ft_put_itoa(n, ret + len(n) - 1);
	return (ret);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:41:24 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:19:58 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (*alst == (void*)0)
		(*alst) = new;
	else
	{
		if ((*alst)->next)
			ft_lstadd_back(&(*alst)->next, new);
		else
			(*alst)->next = new;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:58:20 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:21:13 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list *node;

	node = new;
	node->next = *alst;
	*alst = node;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 20:41:34 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:22:14 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if ((*lst)->next)
		ft_lstclear(&(*lst)->next, del);
	ft_lstdelone(*lst, del);
	*lst = NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:47:10 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:34:34 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst != NULL && del != NULL)
	{
		del(lst->content);
		free(lst);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 20:52:55 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:35:17 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:36:48 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:24:18 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst != (void*)0)
		return ((lst->next) ? ft_lstlast(lst->next) : lst);
	return ((void*)0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:18:13 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:36:34 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *add;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	lst = lst->next;
	while ((lst))
	{
		if (!(add = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, add);
		lst = lst->next;
	}
	return (new);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:33:04 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list *node;

	if (!(node = (t_list*)malloc(sizeof(t_list))))
		return (0);
	node->content = content;
	node->next = 0;
	return (node);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:32:35 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/02/21 18:15:40 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		i;
	// t_list	*tmp;

	i = 0;
	// tmp = lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:49:11 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:34:19 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*pd;
	unsigned char	*ps;
	size_t			i;

	i = -1;
	pd = (unsigned char*)dst;
	ps = (unsigned char*)src;
	while (++i < n)
	{
		pd[i] = ps[i];
		if (ps[i] == (unsigned char)c)
			return (&pd[i + 1]);
	}
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:39:47 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:37:52 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)&ptr[i]);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:04:42 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:38:26 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ps1;
	unsigned char	*ps2;
	size_t			i;

	i = 0;
	if (!n || (s1 != NULL && s2 == s1))
		return (0);
	ps1 = (unsigned char*)s1;
	ps2 = (unsigned char*)s2;
	while (ps1[i] == ps2[i] && i < n - 1)
		i++;
	return (ps1[i] - ps2[i]);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:01:13 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/02/21 18:16:00 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pd;
	unsigned char	*ps;
	size_t			i;
	// size_t			len;

	// len = 0;
	i = -1;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	pd = (unsigned char*)dst;
	ps = (unsigned char*)src;
	if (!ft_memcmp(dst, src, n))
		return (dst);
	if (!n)
		return (dst);
	while (++i < n)
		pd[i] = ps[i];
	return (dst);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:03:44 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:41:01 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pd;
	unsigned char	*ps;
	int				i;
	int				add;

	if (!dst && !src)
		return (NULL);
	i = 0;
	add = 1;
	pd = (unsigned char*)dst;
	ps = (unsigned char*)src;
	if (dst == src)
		return (dst);
	if (!len)
		return (dst);
	i = (pd > ps && pd < ps + len) ? len - 1 : 0;
	add = (i != 0) ? -1 : 1;
	while (len--)
	{
		pd[i] = ps[i];
		i += add;
	}
	return (dst);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:38:09 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 15:44:14 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	int				i;

	if (!len)
		return (b);
	i = -1;
	ptr = b;
	while (len--)
		ptr[++i] = (unsigned char)c;
	return (b);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:46:29 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/14 23:50:21 by ael-ghem         ###   ########.fr       */
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
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 00:02:41 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:39:26 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 00:09:05 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:50:18 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int nb;

	nb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb / 10)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:59:39 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 16:12:44 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:07:06 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				l(char const *s, int i, char c)
{
	int count;

	count = 1;
	while (s[i])
	{
		if (s[i + 1] != c && s[i + 1] != '\0')
			count++;
		else
			break ;
		i++;
	}
	return (count);
}

static int				c_words(char const *str, char c)
{
	int words;
	int is_c;
	int i;

	i = 0;
	words = 0;
	is_c = 1;
	while (str[i])
	{
		if (str[i] == c)
			is_c = 1;
		else if (is_c == 1)
		{
			is_c = 0;
			words++;
		}
		i++;
	}
	return (words);
}

static int				d_job(char const *str, char c, int j, char **ret)
{
	int k;

	while (c_words(str, c))
	{
		while (*str == c || *str == '\0')
			str++;
		if (str)
		{
			k = 0;
			if (!(ret[j] = (char*)malloc(sizeof(char) * (l(str, 0, c) + 1))))
			{
				while (j)
					free(ret[--j]);
				return (-1);
			}
			while (*str != c && *str != '\0')
				ret[j][k++] = *str++;
			ret[j++][k] = '\0';
		}
	}
	return (j);
}

char					**ft_split(char const *str, char c)
{
	char	**ret;
	int		j;

	j = 0;
	ret = NULL;
	if (!str ||
	!(ret = (char**)malloc(sizeof(char*) * (c_words(str, c) + 1))))
		return (NULL);
	j = d_job(str, c, j, ret);
	if (j == -1)
	{
		free(ret);
		ret = NULL;
		return (NULL);
	}
	ret[j] = 0;
	return (ret);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:24:50 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:40:11 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return ((char*)&s[i]);
	}
	if (s[i] == c)
		return ((char*)&s[i]);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:09:02 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		lensrc;
	char	*ptr;
	int		i;

	i = -1;
	lensrc = (int)ft_strlen(s1);
	if (!(ptr = (char*)malloc(lensrc + 1)))
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	ptr[i] = '\0';
	return (ptr);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:35:13 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/16 16:47:38 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len_s1;
	size_t	len_s2;

	ret = NULL;
	if (s1)
	{
		len_s1 = ft_strlen(s1);
		if (s2 == NULL)
			return (ret = ft_strdup(s1));
		len_s2 = ft_strlen(s2);
		ret = (char *)ft_calloc(sizeof(char), len_s1 + len_s2 + 1);
		if (ret)
		{
			ft_strlcpy(ret, s1, len_s1 + 1);
			ft_strlcat((ret + len_s1), s2, len_s2 + len_s1 + 1);
		}
	}
	return (ret);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:04:14 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 19:00:52 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		len;
	size_t		n;

	d = dst;
	s = src;
	n = size;
	while (n-- && *d != '\0')
		d++;
	len = d - dst;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(s));
	while (*s != '\0')
	{
		if (n != 1 && n--)
			*d++ = *s;
		s++;
	}
	*d = '\0';
	return (len + (s - src));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:07:23 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:40:49 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

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
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:47:37 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/05/28 17:10:58 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 22:11:16 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*ptr;

	if (!f || !s)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	if (!(ptr = (char*)malloc(len + 1)))
		return (0);
	while (++i < len)
		ptr[i] = f(i, s[i]);
	ptr[i] = '\0';
	return (ptr);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:56:04 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:42:03 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = -1;
	while (++i < n && (s1[i] || s2[i]))
	{
		if ((int)s1[i] < 0 || (int)s2[i] < 0)
			return (1);
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:32:30 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:42:29 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (needle[0] == 0)
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		if (needle[j++] == haystack[i])
		{
			while (needle[j] && haystack[i + j] && needle[j] == haystack[i + j])
				j++;
			if (!needle[j] && (i + j) <= len)
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:22:16 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/23 15:42:43 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = -1;
	ptr = 0;
	while (s[++i])
	{
		if (s[i] == c)
			ptr = (char*)&s[i];
	}
	if (s[i] == c)
		return ((char*)&s[i]);
	return ((char*)ptr);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:54:28 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_assign(int cf, int cd, char const *s)
{
	char	*ret;

	ret = NULL;
	if (cf >= (int)ft_strlen(s))
	{
		if (!(ret = (char*)malloc(1)))
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	else if ((cf + cd) != 0 && cf != (int)ft_strlen(s))
	{
		if ((ret = (char *)ft_calloc(ft_strlen(s)
		- (cd + cf) + 1, sizeof(char))))
			ft_strlcpy(ret, (s + cd), (ft_strlen(s) - (cd + cf)) + 1);
	}
	else
		ret = ft_strdup(s);
	return (ret);
}

char		*ft_strtrim(char const *s, char const *set)
{
	int		len;
	int		cd;
	int		cf;

	if (!s)
		return (NULL);
	if (!set)
		return (ft_strdup(s));
	cd = 0;
	cf = 0;
	len = (ft_strlen(s) - 1);
	while (ft_strchr(set, s[cd]))
		cd++;
	while (ft_strchr(set, s[len]))
	{
		len--;
		cf++;
	}
	return (ft_assign(cf, cd, s));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:23:59 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		if (!(sub = (char*)malloc(sizeof(char))))
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (!(sub = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

char	*ft_subtoken(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

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
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:19:12 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 16:08:46 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:13:21 by ael-ghem          #+#    #+#             */
/*   Updated: 2019/10/21 16:09:04 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
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

#include "minishell.h"

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

#include "minishell.h"

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
/*   Updated: 2021/07/15 10:48:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		tok[i] = replace_dollar(tok + i);
		print_types(tok[i].type, tok[i].nb, tok[i].tokens);
	}
    bs = bs_position(commands);
    if (bs == 0)
    {
        ft_error("This Shell does not support unspecified special characters \"\\\"", 0);
    }
    else
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

#include "minishell.h"

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

#include "minishell.h"

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

#include "minishell.h"

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

#include "minishell.h"

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

#include "minishell.h"

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
/*   line_handling_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:34:22 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/12 14:06:29 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	separator.nb_separator = count_separators(line, separator_type);
	separator.separator_index = malloc(separator.nb_separator * sizeof(int));
	if (separator.separator_index == NULL)
		ft_error(NULL, 1);
	while (line[++i])
	{
		if ((line[i] == 39 || line[i] == 34) && (count_bs(line, i) % 2 == 0))
			quote = set_quote_value(line[i], quote);
		else if (line[i] == separator_type && (count_bs(line, i) % 2 == 0))
			if (!quote.s_quote && !quote.d_quote)
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

#include "minishell.h"

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
/*   index_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:03:02 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

#include "minishell.h"

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
/*   Updated: 2021/07/16 17:18:32 by abelarif         ###   ########.fr       */
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

		/*	TOK TYPES	*/
# define CMD        9001	/*	command			*/
# define ARG        9002	/*	arguments		*/
# define REDO0		9003	/*	>				*/
# define REDO1		9004	/*	>>				*/
# define REDI0		9005	/*	<				*/
// #define REDI0		9006	/*	<<				*/
# define FILE		9007	/*	file			*/
# define ERROR		9008	/*	error			*/
# define PROTECTED0	9009	/*	protected arg	*/
# define PROTECTED1	9010	/*	protected arg	*/
# define SKIPED		9011	/*	skiped tok		*/

		/*	DBG TOOLS	*/
# define DBG		    while(1){printf("DBG\n");}
# define	SLEEP(A)	printf(A); sleep(5)

typedef struct s_quote
{
	bool            	s_quote;
	bool            	d_quote;
}               		t_quote;

typedef	struct s_env
{
	char	**env;		//free_exit
	char	**sorted;	//free_exit
	char	**history;
    int     history_size;
	int		size;
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

t_env					g_env;

int						max_of(int i, int j);
int						count_bslash(char *line);
int						count_tokens(char *line);
int						bs_position(char **tokens);
int						*set_tok_types(t_tokens tok);
int                     to_execution2(t_tokens *tokens);
int						count_bs(char *line, int index);
int						*get_bslash_index(char *line, int nb);
int						ft_error(char *description, int exitstat);

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
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:58:13 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/05/14 10:52:36 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "minishell.h"

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *haystack,
				const char *needle, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_subtoken(char const *s, unsigned int start, size_t len);

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));

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
