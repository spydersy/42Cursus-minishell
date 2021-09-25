#include "../minishell.h"

int get_fd(int index, t_execution *execution, int i)
{
    int     fd;
    char    *heredoc_path;

    fd = 0;
    if (abs_value(execution[index].files_type[i]) == abs_value(REDI0))
    {
        fd = open(execution[index].files[i], O_RDONLY, 0644);
        printf("%sHADA HWA LFILE DESCRITOR (1): %d%s\n", KYEL, fd, KWHT);
    }
    else if (abs_value(execution[index].files_type[i]) == abs_value(HEREDOC))
    {
        heredoc_path = ft_strjoin("/tmp/", execution[index].files[i]);
        fd = open(heredoc_path, O_RDONLY, 0644);
        free(heredoc_path);
        printf("%sHADA HWA LFILE DESCRITOR (2): {%s} %d%s\n", KYEL, heredoc_path, fd, KWHT);
    }
    else if (abs_value(execution[index].files_type[i]) == abs_value(REDO0))
    {
        fd = open(execution[index].files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        printf("%sHADA HWA LFILE DESCRITOR (3): %d%s\n", KYEL, fd, KWHT);
    }
    else if (abs_value(execution[index].files_type[i]) == abs_value(REDO1))
    {
            fd = open(execution[index].files[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
        printf("%sHADA HWA LFILE DESCRITOR (4): %d%s\n", KYEL, fd, KWHT);
    }
    if (fd == -1)
    {
        ft_error(NULL, 0);
    }
    return (fd);
}

int *open_files(int index, t_execution *execution)
{
    int     i;
    int     *fds;

    i = 0;
    while (execution[index].files[i])
        i++;
    if (i != 0)
        fds = malloc(sizeof(int) * i);
    else
        return (0);
    while (execution[index].files[++i])
    {
        fds[i] = get_fd(index, execution, i);
    }
    return (fds);
}

t_execution    input_output_duplication(int index, int *pipes, t_execution *execution)
{
    if (pipes){}
    
    execution[index].fds = open_files(index, execution);

    // if (index == 0) //  FIRST
    // {
    //     fd_to_dup = open_files(index, execution);
    // }
    // else if (index == execution[0].nb_pipelines - 1)    //  LASTT
    // {
    //     fd_to_dup = open_files(index, execution);
    // }
    // else    //  MIDDLE
    // {
    //     fd_to_dup = open_files(index, execution);
    // }
    return (execution[index]);  
}