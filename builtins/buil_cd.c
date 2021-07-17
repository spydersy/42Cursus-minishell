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
