/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 10:10:24 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/24 07:14:24 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1
# define APPFILE 2
typedef struct s_data{
	int		infd;
	int		outfd;
	int		*status;
	char	**envp;
	char	**av;
	int		ac;
	int		pipenb;
}		t_data;

int		ft_strnchr(char *str, char c);
char	*ft_strndup(char *str, unsigned int n);
char	*join_path(char *path, char *bin);
int		ft_strncmp(char *str1, char *str2, int n);
char	**ft_split(char *str, char sep);
int		openfile(char *filename, int mode);
void	redir(char *cmd, char **envp, int fd, int *status);
void	exec(char *cmd, char **envp);
char	*here_doc(char *path, char **av);
void	check_fds(int infd, int outfd, int ac, char **av);
void	execute(t_data *data);

#endif
