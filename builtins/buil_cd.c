/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 14:36:48 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/15 13:00:03 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void        exec_cd(char *path)
// {
    // int     ret;
    // char    *old_pwd;
    // char    *new_pwd;

    // old_pwd = builtin_pwd(1);
    // ret = chdir(path);
    // if (ret == 0)
    // {
        // new_pwd = builtin_pwd(1);
    // }
// }

void        builtin_cd(char **path)
{
    int ret;
    char    *old_pwd;
    char    *new_pwd;

    printf("cd DBG : [%s]\n", path[0]);
    if (path[0] == NULL)
    {
        ret = chdir("/Users/abelarif");
        if (ret == -1)
            ft_error(NULL, 0);
        new_pwd = builtin_pwd(1);
    old_pwd = builtin_pwd(1);
        set_env("OLDPWD", old_pwd);
        set_env("PWD", new_pwd);
        free(old_pwd);
        free(new_pwd);
        return ;
    }
    ret = chdir(path[0]);
    if (ret == -1)
        ft_error(NULL, 0);
    else
    {
        new_pwd = builtin_pwd(1);

        old_pwd = builtin_pwd(1);
        set_env("OLDPWD", old_pwd);
        set_env("PWD", new_pwd);
        free(old_pwd);
        free(new_pwd);
    }
}
