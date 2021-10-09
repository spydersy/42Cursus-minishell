/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:01:07 by abelarif          #+#    #+#             */
/*   Updated: 2021/10/08 15:32:54 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_is_present(char *str)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			count++;
	}
	return (count);
}

char	*ft_charjoin(char *str, char c)
{
	int		i;
	int		len;
	char	*ret;

	i = -1;
	len = ft_strlen(str) + 1;
	if (c != '\0')
		len++;
	ret = malloc(sizeof(char) * len);
	while (str[++i])
	{
		ret[i] = str[i];
	}
	if (c != '\0')
		ret[i++] = c;
	ret[i] = '\0';
	free(str);
	return (ret);
}

char	*sub_dollar(char *str, int index)
{
	int		i;
	char	*tmp;

	i = index;
	while (str[++i])
	{
		if ((str[i] == ' ' || str[i] == '\t') && i == index + 1)
			return (ft_strdup("$"));
		else if ((str[i] == ' ' || str[i] == '\t'))
		{
			tmp = ft_substr(str, index, i - index);
			dollar_handling(&tmp, 0);
			return (tmp);
		}
	}
	if (str[i - 1] == '$')
		return (ft_strdup("$"));
	tmp = ft_substr(str, index, i - index);
	dollar_handling(&tmp, 0);
	return (tmp);
}

int	dollar_len(char *str, int index)
{
	int	i;

	i = index;
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (i - index);
	}
	return (i - index);
}

char	*expand_dollars(char *str)
{
	int		i;
	char	*content;
	char	*tmp;

	i = -1;
	content = ft_strdup("");
	while (str[++i])
	{
		if (str[i] != '$')
		{
			content = ft_charjoin(content, str[i]);
		}
		else
		{
			tmp = sub_dollar(str, i);
			content = ft_strjoin(content, tmp);
			i += dollar_len(str, i) - 1;
		}
	}
	return (content);
}

char	*expand_quotes(char *content, int index)
{
	int		nb_dollars;
	char	*tmp;

	tmp = ft_substr(content, index + 1, ft_strlen(content) - 2 - index);
	nb_dollars = dollar_is_present(tmp);
	if (content[index] == '\"' && nb_dollars != 0)
	{
		tmp = expand_dollars(tmp);
	}
	return (tmp);
}

t_tokens	select_quotes(t_tokens tokens)
{
	int		i;
	int		dqIndex;

	i = -1;
	while (tokens.tokens[++i])
	{
		dqIndex = 0;
		if (i != 0)
			dqIndex++;
		if (tokens.tokens[i][dqIndex] == '\"'
			|| tokens.tokens[i][dqIndex] == '\'')
		{
			tokens.tokens[i]
				= expand_quotes(tokens.tokens[i], dqIndex);
		}
	}
	return (tokens);
}

void	expand_quotes_dollar(t_tokens *tokens)
{
	int		i;

	i = -1;
	while (++i < tokens[0].pipe)
	{
		tokens[i] = select_quotes(tokens[i]);
	}
	execution(tokens);
}
