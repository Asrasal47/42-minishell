/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:09:22 by arasal            #+#    #+#             */
/*   Updated: 2023/04/14 17:17:23 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verify_quotes(t_minishell *m)
{
	int	i;
	int	s;
	int	b;

	i = 0;
	s = 0;
	b = 0;
	while (m->cmd_line[i])
	{
		if (m->cmd_line[i] == '\'')
			s++;
		if (m->cmd_line[i] == '\"')
			b++;
		i++;
	}
	if ((s % 2 == 1) || (b % 2 == 1))
		return (0);
	return (1);
}

int	verify_pipe(t_minishell *m)
{
	int	is_word;
	int	is_pipe;
	int	i;

	is_word = 0;
	is_pipe = 0;
	i = 0;
	if (m->tokens[0][0] == '|')
		return (0);
	while (m->tokens[i])
	{
		if (ft_isalpha(m->tokens[i][0]) || access(m->tokens[i], F_OK))
			is_word = 1;
		else if (is_word && ft_strcmp(m->tokens[i], "|") == 0)
		{	
			is_pipe ++;
			is_word = 0;
		}
		else if (!is_word && ft_strcmp(m->tokens[i], "|") == 0)
			return (0);
		i++;
	}
	if (is_word == 0 && is_pipe)
		return (0);
	return (1);
}

static int	verify_redirections_helper(t_minishell *m, int i)
{
	int	j;

	if (m->tokens[i][0] == '<' || m->tokens[i][0] == '>')
	{
		j = 0;
		while (m->tokens[i][j] == '>' || m->tokens[i][j] == '<')
			j++;
		if (j > 2)
			return (0);
	}
	j = -1;
	while (m->tokens[i][++j])
	{
		if (m->tokens[i][j] == '>' && !m->tokens[i][j + 1] && !m->tokens[i + 1])
			return (0);
		if (m->tokens[i][j] == '<' && !m->tokens[i][j + 1] && !m->tokens[i + 1])
			return (0);
		if (m->tokens[i][j] == '>' && m->tokens[i][j + 1]
			&& m->tokens[i][j + 1] == '<')
			return (0);
		if (m->tokens[i][j] == '<' && m->tokens[i][j + 1]
			&& m->tokens[i][j + 1] == '>')
			return (0);
	}
	return (1);
}

int	verify_redirections(t_minishell *m)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	quotes = 0;
	while (m->tokens[i])
	{
		if (!verify_redirections_helper(m, i))
			return (0);
		if ((ft_strcmp(m->tokens[i], ">") == 0
				|| ft_strcmp(m->tokens[i], ">>") == 0
				|| ft_strcmp(m->tokens[i], "<") == 0
				|| ft_strcmp(m->tokens[i], "<<") == 0)
			&& (!m->tokens[i + 1] || (!ft_isalpha(m->tokens[i + 1][0])
				&& m->tokens[i + 1][0] != '/' && m->tokens[i + 1][0] != '\'')))
			return (0);
		i++;
	}
	return (1);
}

int	verify_syntax(t_minishell *m)
{
	m->tokens = ft_split(m->line, ' ');
	if (!verify_quotes(m)
		|| !verify_pipe(m)
		|| !verify_redirections(m))
	{
		free_s(m->tokens);
		free(m->cmd_line);
		free(m->line);
		g_glob.exit_status = 2;
		return (0);
	}
	free_s(m->tokens);
	free(m->cmd_line);
	return (1);
}
