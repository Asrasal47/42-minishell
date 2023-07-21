/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:33:56 by arasal            #+#    #+#             */
/*   Updated: 2023/04/17 16:32:06 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exec_heredoc_helper3(t_minishell *m, int i, char **s)
{
	char	**t;

	t = NULL;
	if (i == 0 && !ft_strcmp(m->tokens[i], "<<") && m->tokens[i + 1]
		&& ft_strchr(m->tokens[i + 1], ' '))
	{
		t = ft_split(m->tokens[i + 1], ' ');
		m->line = ft_strdup(t[1]);
		free(*s);
		(*s) = ft_strdup(t[0]);
		m->line = ft_strdup(t[1]);
		free_s(t);
	}
	else if (i == 0 && m->tokens[i + 1])
		m->line = ft_strdup(m->tokens[i + 1]);
	else if (i > 0)
		m->line = ft_strdup(m->tokens[i - 1]);
	else
		m->line = ft_strdup(" ");
}

static void	exec_heredoc_helper2(t_minishell *m, int i, char **s)
{
	int		j;

	if (i == 0 && !strnstr(m->tokens[i], "<<", 2) && !m->tokens[i + 1])
	{
		j = 0;
		while (m->tokens[i][j] != '<')
			j++;
		m->line = ft_substr(m->tokens[i], 0, j);
		j += 2;
		*s = ft_substr(m->tokens[i], j, ft_strlen(m->tokens[i]) - j);
	}
	if (i == 0 && !strnstr(m->tokens[i], "<<", 2) && m->tokens[i + 1])
	{
		j = 0;
		while (m->tokens[i][j] != '<')
			j++;
		m->line = ft_substr(m->tokens[i], 0, j);
		*s = ft_strdup(m->tokens[i + 1]);
	}
}

static void	exec_heredoc_helper(t_minishell *m, int i, char **s)
{
	int		j;

	if (i == 0 && !strnstr(m->tokens[i], "<<", 2))
	{
		exec_heredoc_helper2(m, i, s);
		return ;
	}
	else if (m->tokens[i][2])
	{
		j = 2;
		while (m->tokens[i][j] && m->tokens[i][j] == ' ')
			j++;
		*s = ft_strdup(&m->tokens[i][j]);
	}
	else if (!m->tokens[i][2] && m->tokens[i + 1])
		*s = ft_strdup(m->tokens[i + 1]);
	exec_heredoc_helper3(m, i, s);
}

void	exec_heredoc(t_minishell *m)
{
	char	*s;
	int		i;

	i = -1;
	m->temp_fd = dup(STDIN_FILENO);
	free(m->line);
	while (m->tokens[++i])
	{
		if (ft_strnstr(m->tokens[i], "<<", ft_strlen(m->tokens[i])))
		{
			exec_heredoc_helper(m, i, &s);
			break ;
		}
	}
	here_doc_pipe(s, m);
	free(s);
	if (((ft_arrlen(m->tokens) > 1 && ft_strcmp(m->tokens[0], "<<"))
			|| (!ft_strcmp(m->tokens[0], "<<") && ft_strchr(m->tokens[i + 1],
					' ')) || !strnstr(m->tokens[0], "<<", 2)))
		exec_simple(m->line, m);
	else
		ft_clear(m);
	if (dup2(m->temp_fd, STDIN_FILENO) == -1)
		strerror(EBADF);
	close(m->temp_fd);
}
