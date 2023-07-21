/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:39:30 by arasal            #+#    #+#             */
/*   Updated: 2023/04/17 14:57:17 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_quotes_fix(char **w, char *s, int *i)
{
	if (*i == 0)
		(*w)[*i] = '0';
	else
		(*w)[*i] = '3';
	while (s[++(*i)] == ' ' && s[(*i) + 1] == ' ')
		(*w)[*i] = '0';
}

int	is_pipe(t_minishell *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	m->pipes = 0;
	while (m->line[i] != '\0')
	{
		if (m->line[i] == '\'' || m->line[i] == '\"')
			j += 1;
		if (m->line[i] == '|' && j % 2 == 0)
			m->pipes += 1;
		i++;
	}
	if (m->pipes > 0)
		return (1);
	return (0);
}

int	is_builtin(t_minishell *mshell)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "exit",
		"export", "unset", "env"};
	int			i;
	char		**temp;
	char		*tmp;

	i = 0;
	tmp = ft_quotes(mshell->cmds->cmd);
	free(mshell->cmds->cmd);
	mshell->cmds->cmd = ft_strdup(tmp);
	free(tmp);
	temp = ft_split(mshell->cmds->cmd, '/');
	while (temp && temp[i])
		i++;
	if (i > 0)
	{
		free(mshell->cmds->cmd);
		mshell->cmds->cmd = ft_strdup(temp[i - 1]);
	}
	free_s(temp);
	i = 0;
	while (i < 7)
		if (ft_strcmp(ft_strlower(mshell->cmds->cmd), builtins[i++]) == 0)
			return (1);
	return (0);
}

int	is_here_doc(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->tokens[i])
	{
		if (ft_strnstr(m->tokens[i], "<<", ft_strlen(m->tokens[i]))
			&& !ft_strnstr(m->tokens[i], "\'<<\'", ft_strlen(m->tokens[i]))
			&& !ft_strnstr(m->tokens[i], "\"<<\"", ft_strlen(m->tokens[i])))
			return (1);
		i++;
	}
	return (0);
}

int	parse_command(t_minishell *mshell)
{
	if (is_pipe(mshell))
		parsing_pipe(mshell);
	else if (is_here_doc(mshell))
		exec_heredoc(mshell);
	else if (is_builtin(mshell))
		exec_builtin(mshell);
	else if (ft_strcmp(mshell->cmds->cmd, "$?") == 0)
	{
		dprintf(2, "%s : %s: %s\n", "minishell",
			ft_itoa(g_glob.exit_status), "command not found");
		ft_clear(mshell);
	}	
	else
		exec_simple(mshell->line, mshell);
	return (1);
}
