/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 07:17:47 by ael-ghem          #+#    #+#             */
/*   Updated: 2021/07/05 09:37:30 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strnchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_strndup(char *s, unsigned int n)
{
	char				*ret;
	unsigned int		i;

	i = 0;
	ret = malloc(sizeof(char) * (n + 1));
	while (i < n)
		ret[i++] = *s++;
	ret[n] = 0;
	return (ret);
}

char	*join_path(char *path, char *bin)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char)
			*(ft_strnchr(path, 0) + ft_strnchr(bin, 0) + 2));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (path[j])
		ret[i++] = path[j++];
	ret[i++] = '/';
	j = 0;
	while (bin[j])
		ret[i++] = bin[j++];
	ret[i] = 0;
	return (ret);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	while (--n > 0 && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s2 - *s1);
}

char	**ft_split(char *s, char sep)
{
	char	**ret;
	int		words;
	int		i;
	int		j;

	words = 0;
	j = 0;
	while (s[j])
		if (s[j++] == sep)
			words++;
	ret = malloc(sizeof(char *) * (words + 2));
	ret[words + 1] = NULL;
	i = 0;
	while (i < words + 1)
	{
		j = 0;
		while (s[j] && s[j] != sep)
			j++;
		ret[i++] = ft_strndup(s, j);
		s = s + j + 1;
	}
	return (ret);
}
