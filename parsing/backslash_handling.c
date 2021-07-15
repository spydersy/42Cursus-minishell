/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:21:31 by abelarif          #+#    #+#             */
/*   Updated: 2021/06/11 17:06:25 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_bs(char *line, int index)
{
	int	c;

	c = 0;
	if (index == 0)
		return (0);
	while (index-- >= 0)
	{
		if (index >= 0 && line[index] == '\\')
			c++;
		else
			break ;
	}
	return (c);
}
