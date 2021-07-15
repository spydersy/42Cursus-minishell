/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 22:11:16 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/06/05 20:10:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*ptr;

	if (!f || !s)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	if (!(ptr = (char*)malloc(len + 1)))
		return (0);
	while (++i < len)
		ptr[i] = f(i, s[i]);
	ptr[i] = '\0';
	return (ptr);
}
