/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 14:36:48 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/10 13:56:09 by abelarif         ###   ########.fr       */
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

    old_pwd = builtin_pwd(1);
    ret = chdir(path);
    if (ret == -1)
        ft_error(NULL, 0);
    else
    {
        new_pwd = builtin_pwd(1);
        /*
        set_env("OLDPWD", old_pwd);
        set_env("PWD", new_pwd);
        free(old_pwd);
        free(new_pwd);
        */
    }
}
