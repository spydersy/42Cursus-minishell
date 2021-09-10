/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 14:36:48 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/10 12:20:33 by abelarif         ###   ########.fr       */
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
    int ret
}
