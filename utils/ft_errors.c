/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:08:49 by abelarif          #+#    #+#             */
/*   Updated: 2021/09/10 13:41:38 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error(char *description, int exitstat)
{
	/* FREE */
	write(2, KRED, ft_strlen(KRED));
	write(2, "Error\n", 6);
	if (description)
	{
		write(2, description, ft_strlen(description));
	}
	else
	{
		write(STDERR, strerror(errno), ft_strlen(strerror(errno)));
	}
	write(2, "\n", 1);
	write(1, KWHT, ft_strlen(KWHT));
	if (exitstat == 1)
		exit(EXIT_FAILURE);
	return (errno);
}
