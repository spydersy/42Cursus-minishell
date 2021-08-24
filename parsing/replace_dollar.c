/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:18:54 by abelarif          #+#    #+#             */
/*   Updated: 2021/08/24 11:26:12 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_search(char *str, int index)
{
	int			i;
	int			lensrc;
	char		*env;

	env = NULL;
	i = -1;
	if (index != 0)
		index = 1;
	lensrc = ft_strlen(str + index);
	while (g_env.sorted[++i])
	{
		if (ft_strncmp(str + 1 + index, g_env.sorted[i], lensrc - 1) == 0
			&& g_env.sorted[i][lensrc - 1] == '=')
		{
			env = ft_substr(g_env.sorted[i], lensrc,
					ft_strlen(g_env.sorted[i]) - lensrc + 2);
			free(str);
			str = NULL;
			return (env);
		}
	}
	free(str);
	str = NULL;
	return (ft_strdup(""));
}

void	dollar_handling(char **tok, int index)
{
	char		*str;

	str = ft_strdup(*tok);
	free(*tok);
	*tok = NULL;
	*tok = env_search(str, index);
	if (*tok == NULL)
		ft_error("tok", 1);
}

int	count(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	free_dollar(char **old, char **content)
{
	int		i;

	i = -1;
	while (old[++i])
	{
		free(old[i]);
		old[i] = NULL;
	}
	i = -1;
	while (content[++i])
	{
		free(content[i]);
		content[i] = NULL;
	}
	free(old);
	free(content);
	old = NULL;
	content = NULL;
}

char	**split_dollar_signe(char **old, int index)
{
	int		i;
	int		c;
	char	**content;
	char	**new;

	i = -1;
	content = ft_split(old[index], ' ');
    printf("COUNT CONTENT : %d\n", count(content));
    printf("COUNT OLD     : %d\n", count(old));
    printf("------- INDEX : %d\n", index);
	new = malloc(sizeof(char *) * (count(old) + count(content)));
	while (++i < index)
		new[i] = ft_strdup(old[i]);
	c = -1;
	while (content[++c])
	{
		new[i] = ft_strdup(content[c]);
		i++;
	}
	c = index;
	while (old[++c])
	{
		new[i] = ft_strdup(old[c]);
		i++;
	}
	new[i] = NULL;
	free_dollar(old, content);
	return (new);
}

void	set_types(t_tokens *tok, int oldlen, int newlen, int index)
{
	int		i;
	int		c;
	int		*newtype;

	i = -1;
	newtype = malloc(sizeof(int) * newlen);
	while (++i < index)
		newtype[i] = tok->type[i];
	c = -1;
	while (++c < newlen - oldlen + 1)
	{
		if (c == 0)
			newtype[i] = PROTECTED0;
		else
			newtype[i] = PROTECTED1;
		i++;
	}
	c = index;
	while (++c < oldlen)
	{
		newtype[i] = tok->type[c];
		i++;
	}
	free(tok->type);
	tok->type = newtype;
}

t_tokens	replace_dollar(t_tokens *tok)
{
	int			i;
	int			presence;
	int			oldlen;
	int			newlen;

	presence = 1;
	oldlen = count(tok->tokens);
	newlen = oldlen;
	i = -1;
	while (presence)
	{
		presence = 0;
		while (tok->tokens[++i])
		{
			if (tok->tokens[i][1] == '$'
				|| (i == 0 && tok->tokens[i][0] == '$'))
			{
				dollar_handling(&(tok->tokens[i]), i);
				tok->tokens = split_dollar_signe(tok->tokens, i);
                // print_toks(tok->tokens, 5);
				presence = 1;
				newlen = count(tok->tokens);
				if (oldlen != newlen)
					set_types(tok, oldlen, newlen, i);
				else if (tok->type[i] < 0)
					tok->type[i] = -PROTECTED0;
				else
					tok->type[i] = PROTECTED0;
				if (tok->type[0] == PROTECTED0 || tok->type[0] == -PROTECTED0)
					tok->type[i] = -CMD;
				i += newlen - oldlen;
				oldlen = newlen;
				break ;
			}
		}
		tok->nb = i;
	}
	return (*tok);
}
