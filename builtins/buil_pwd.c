/* ************************************************************************** */
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
