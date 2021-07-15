/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:23:59 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		if (!(sub = (char*)malloc(sizeof(char))))
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (!(sub = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

char	*ft_subtoken(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	i = 0;
	sub = malloc(sizeof(char) * (len - start + 1));
	if (sub == NULL)
		ft_error("malloc", 1);
	while (start < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
