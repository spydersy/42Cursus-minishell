/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_of.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:04:08 by abelarif          #+#    #+#             */
/*   Updated: 2021/07/15 10:22:26 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	max_of(int i, int j)
{
	if (i < j)
		return (j);
	else
		return (i);
}