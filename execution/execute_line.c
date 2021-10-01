/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:59:02 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/22 12:17:33 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*init_pipes(int nb_pipes)
{
	int		i;
	int		*pipes;

	i = -1;
	pipes = malloc(sizeof(int) * 2 * nb_pipes);
	while (++i < nb_pipes)
	{
		pipe(pipes + i * 2);
	}
	return (pipes);
}

void	close_all_fds(int *pipes, int nb_pipes)
{
	int		i;

	i = -1;
	while (++i < nb_pipes * 2)
	{
		close(pipes[i]);
	}
}

int	*get_fds_files(int index, t_execution *execution)
{
	int		i;
	int		*fds;

	i = 0;
	while (execution[index].files[i])
		i++;
	if (i)
		fds = malloc(sizeof(int) * i);
	else
		return (NULL);
	i = -1;
	while (execution[index].files[++i])
	{
		fds[i] = get_fd(index, execution, i);
	}
	return (fds);
}

void	input_file_error(char *file)
{
	ft_putstr_fd(KRED, 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": No such file or directory", 2);
	ft_putstr_fd(KNRM, 2);
}

int	check_redirections_errors(int index, t_execution *execution)
{
	int		i;

	i = -1;
	while (execution[index].files[++i])
	{
		if (abs_value(execution[index].files_type[i]) == REDI0 && execution[index].fds[i] == -1)
		{
			input_file_error(execution[index].files[i]);
			return (-1);
		}
	}
	return (0);
}

int	is_input_redir(int file_type)
{
	if (abs_value(file_type) == REDI0)
		return (1);
	if (abs_value(file_type) == HEREDOC)
		return (1);
	return (0);
}

int	is_output_redir(int file_type)
{
	if (abs_value(file_type) == REDO0)
		return (1);
	if (abs_value(file_type) == REDO1)
		return (1);
	return (0);
}

void	dup_input(int index, int input_fd, int *pipes, t_execution *execution)
{
	if (input_fd == -1 && index != 0)
	{
		dup2(pipes[index * 2 - 2], STDIN);
	}
	else if (input_fd != -1)
	{
		dup2(execution[index].fds[input_fd], STDIN);
	}
}

void	dup_output(int index, int output_fd, int *pipes, t_execution *execution)
{
	if (output_fd == -1 && index != execution[0].nb_pipelines - 1)
	{
		dup2(pipes[index * 2 + 1], STDOUT);
	}
	else if (output_fd != -1)
	{
		dup2(execution[index].fds[output_fd], STDOUT);
	}
}

void	dup_in_out(int index, int *pipes, t_execution *execution)
{
	int		i;
	int		in_index;
	int		out_index;

	i = -1;
	in_index = -1;
	out_index = -1;
	while (execution[index].files[++i])
	{
		if (is_input_redir(execution[index].files_type[i])
			&& execution[index].fds[i] != -1)
			in_index = i;
		else if (is_output_redir(execution[index].files_type[i])
			&& execution[index].fds[i] != -1)
			out_index = i;
	}
	dup_input(index, in_index, pipes, execution);
	dup_output(index, out_index, pipes, execution);
	// close_all_fds(execution[index].fds, i);
}

void	command_not_found_error(char *command)
{
	ft_putstr_fd(KRED, 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	ft_putstr_fd(KNRM, 2);
}

void	no_such_file_error(char *command)
{
	ft_putstr_fd(KRED, 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": No such file or directory", 2);
	ft_putstr_fd(KNRM, 2);
}

void	child_process(int index, int *pipes, t_execution *execution)
{
	int     ret;
	char	*str_exit;

	ret = 0;
	execution[index].fds = get_fds_files(index, execution);
	if (check_redirections_errors(index, execution) != -1)
	{
		dup_in_out(index, pipes, execution);
	}
	else
	{
		// do something ;
		return ;
	}
	close_all_fds(pipes, execution[0].nb_pipelines - 1);
	if (execution[index].exec_path == NULL)
	{
		printf(">>A<<\n");
		command_not_found_error(execution[index].command);
		set_env("?", "127");
		exit(127);
	}
	else if (ft_strlen(execution[index].exec_path) == 0)
	{
		printf(">>B<<\n");
		no_such_file_error(execution[index].command);
		set_env("?", "127");
		exit(127);
	}
	else if (ft_strncmp("builtin", execution[index].exec_path, 7) == 0 && execution[index].exec_path)
	{
		printf(">>C<<\n");
		str_exit = ft_itoa(simple_builtin(execution + index, 1));
		set_env("?", str_exit);
		free(str_exit);
		exit(simple_builtin(execution + index, 1));
	}
	else
	{
		printf(">>D<<\n");
		ret = execve(execution[index].exec_path, execution[index].args, g_env.env);
		ft_error(NULL, 0);
		set_env("?", "126");
		exit(126);
	}
}

void	create_childs(t_execution *execution)
{
	int		i;
	int		*pipes;
	int		status;
	pid_t	pid;

	i = -1;
	pipes = init_pipes(execution[0].nb_pipelines - 1);
	while (++i < execution[0].nb_pipelines)
	{
		pid = fork();
		if (pid == 0)
		{
			child_process(i, pipes, execution);
		}
	}
	close_all_fds(pipes, execution[0].nb_pipelines - 1);
	waitpid(pid, &status, 0);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		g_env.exit_status = WEXITSTATUS(status);
	}
}

t_execution	*execute_line(t_execution *execution)
{
	create_childs(execution);
	printf("%sexit_status :%s %d\n", KYEL, KNRM, g_env.exit_status);
	return (execution);
}
