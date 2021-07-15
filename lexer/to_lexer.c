/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:03:29 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/12 13:06:34 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// #include <unistd.h>
// #include <string.h>
// #include <error.h>
// #include <errno.h>
// #include <stdio.h>
// #include <stdlib.h>

// int     main()
// {
//     char    **str;
    
//     str = malloc(sizeof(char*) * 1);
//     str[0] = strdup("ls -la");
//     str[1] = strdup("to_lexer.c");
//     int ret = execve("/usr/bin/ls", str, NULL);
//     if (ret < 0)
//     {
//         printf("strerror : [%s]\n", strerror(errno));
//     }
// }


// void    toks_reorder(char **toks)
// {
//     int     i;

//     i = -1;
//     while (toks[++i])
//     {
        
//     }
// }

// void    to_lexer(t_tokens *toks)
// {
//     // int     i;

//     // i = -1;
//     // while (++i < toks->pipe)
//     // {
//     //     toks_reorder(toks->tokens);        
//     // }
//     // // ft_error("LEXER", 1);
// }