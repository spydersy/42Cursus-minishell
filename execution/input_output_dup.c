#include "../minishell.h"

int get_fd(int index, t_execution *execution, int i)
{
    int     fd;
    char    *heredoc_path;

    fd = 0;
    if (execution[index].files_type[i] == abs_value(REDI0))
    {
        fd = open(execution[index].files[i], O_RDONLY);
    }
    else if (execution[index].files_type[i] == abs_value(HEREDOC))
    {
        heredoc_path = ft_strjoin("/tmp/", execution[index].files[i]);
        fd = open(execution[index].files[i], O_RDONLY);
        free(heredoc_path);
    }
    else if (execution[index].files_type[i] == abs_value(REDO0))
        fd = open(execution[index].files[i], O_WRONLY | O_CREAT);
    else if (execution[index].files_type[i] == abs_value(REDO1))
        fd = open(execution[index].files[i], O_WRONLY | O_CREAT | O_APPEND);
    if (fd == -1)
    {
        ft_error(NULL, 0);
    }
    return (fd);
}

int open_files(int index, t_execution *execution)
{
    int     i;

    i = 0;
    while (execution[index].files[i])
        i++;
    if (i != 0)
        execution[index].fds = malloc(sizeof(int) * i);
    else
        return (0);
    while (execution[index].files[++i])
    {
        execution[index].fds[i] = get_fd(index, execution, i);
    }
    return (0);
}

t_execution    input_output_duplication(int index, int *pipes, t_execution *execution)
{
    int     fd_to_dup;
    if (pipes){}
    if (index == 0) //  FIRST
    {
        fd_to_dup = open_files(index, execution);
    }
    else if (index == execution[0].nb_pipelines - 1)    //  LASTT
    {
        fd_to_dup = open_files(index, execution);
    }
    else    //  MIDDLE
    {
        fd_to_dup = open_files(index, execution);
    }  
}