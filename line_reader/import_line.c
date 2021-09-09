/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:21:39 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/09 16:10:07 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_window(void)
{
	write(1, "\e[1;1H\e[2J", ft_strlen("\e[1;1H\e[2J"));
}

char	*read_line(void)
{
	char	*line;

	if (get_next_line(0, &line) < 0)
		ft_error("Get Next Line", 1);
    return (line);
}

void	prompt(int sig)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 500);
	if (buffer == NULL)
		ft_error("MALLOC", 1);
	buffer = getcwd(buffer, 500);
	if (sig == 2)
		write(1, "\n", 1);	
	ft_putstr_fd(KGRN, 1);
	ft_putstr_fd("MINISHELL (", 1);
	ft_putstr_fd(KBLU, 1);
	ft_putstr_fd(buffer, 1);
	ft_putstr_fd(KGRN, 1);
	ft_putstr_fd(") > ", 1);
	ft_putstr_fd(KWHT, 1);
	free(buffer);
	// return ();
}

// char	*prompt(void)
// {
// 	char	*pwd;

// 	pwd = malloc(sizeof(char) * 500);
		
// }