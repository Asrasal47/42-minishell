/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:10:31 by arasal            #+#    #+#             */
/*   Updated: 2023/04/13 18:05:20 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_tokenize_helper(char ***tokenized, char *line, int *i, int *j)
{
	char	*temp;

	temp = NULL;
	if (line[(*i) + 1] == '\0')
		temp = ft_substr(line, (*j), (*i) + 1 - (*j));
	else
		temp = ft_substr(line, (*j), (*i) - (*j));
	if (ft_stradd(temp, tokenized))
		return (free_r(temp));
	free(temp);
	if (line[(*i)] == '\t')
	{
		temp = ft_strdup(" ");
		if (ft_stradd(temp, tokenized))
			return (free_r(temp));
		while (line[(*i)] == '\t' && line[(*i) + 1])
			i++;
		free(temp);
	}
	(*j) = (*i) + 1;
	return (line);
}

char	**ft_tokenize(char *line)
{
	char	**tokenized;
	int		i;
	int		j;
	int		quotes;

	i = 0;
	j = 0;
	quotes = 0;
	tokenized = NULL;
	while (line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'') && quotes == 0)
			quotes = 1;
		else if ((line[i] == '\"' || line[i] == '\'') && quotes == 1)
			quotes = 0;
		if ((ft_strchr(" \t\n", line[i]) && (ft_strchr("|><\0\t\n", line[i + 1])
					|| j == 0 || line[j] == '-' || (line[i + i] == '-'
						&& !tokenized[1])) && quotes == 0)
			|| line[i + 1] == '\0')
			if (!ft_tokenize_helper(&tokenized, line, &i, &j))
				return (NULL);
		i++;
	}
	return (tokenized);
}

static int	token_cmd(t_minishell *m, int *i, int x)
{
	if (!m->tokens[1])
	{
		if (m->tokens[0][0] == '$' && x == 0)
		{
			free_s(m->tokens);
			m->tokens = ft_tokenize(ft_variable_expansion(m->line, m, 0));
		}
		else
		{
			m->cmds->cmd = ft_strtrim((m->tokens[(*i)]), "\', \"");
			return (1);
		}
	}
	m->cmds->cmd = ft_variable_expansion(ft_strtrim((m->tokens[(*i)++]),
				"\', \""), m, 0);
	return (0);
}

int	token_maker(t_minishell *m, int x)
{
	int	i;

	i = 0;
	if (is_pipe(m) && x == 0)
		return (1);
	if (x == 0)
		m->tokens = ft_tokenize(m->line);
	if (!m->tokens)
		return (0);
	if (token_cmd(m, &i, x))
		return (1);
	if (!m->tokens[i])
		return (1);
	while (m->tokens[i] && m->tokens[i][0] == '-'
		&& ft_isalpha(m->tokens[i][1]))
		ft_stradd(m->tokens[i++], &m->cmds->option);
	if (!m->tokens[i])
		return (1);
	m->cmds->param = ft_quotes(m->tokens[i]);
	if (m->tokens[i][0] == '\'' && m->tokens[i][1] == '$'
		&& m->tokens[i][ft_strlen(m->tokens[i]) - 1] == '\'')
		;
	else
		m->cmds->param = ft_variable_expansion(m->cmds->param, m, 0);
	return (1);
}
