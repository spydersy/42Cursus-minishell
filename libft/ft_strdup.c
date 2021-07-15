/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:09:02 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		lensrc;
	char	*ptr;
	int		i;

	i = -1;
	lensrc = (int)ft_strlen(s1);
	if (!(ptr = (char*)malloc(lensrc + 1)))
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	ptr[i] = '\0';
	return (ptr);
}
