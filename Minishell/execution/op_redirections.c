/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:33:45 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 15:34:10 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_op_rdr_helper2(t_minishell *m, char *l, char **sp, char **op)
{
	int		i;
	char	**sp2;
	char	*temp;

	i = 0;
	sp2 = NULL;
	while (sp[++i])
	{
		if (sp2)
			free_s(sp2);
		sp2 = ft_split(sp[i], ' ');
		if (sp2[1])
		{
			temp = ft_strjoin(*op, " ");
			free(*op);
			*op = ft_strjoin(temp, sp2[1]);
			free(temp);
		}
		m->red = ft_strtrim(sp2[0], " ");
		if (*(ft_strchr(l, '>') + 1) == '>')
			m->redirect[1] = open(m->red, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			m->redirect[1] = open(m->red, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	free_s(sp2);
}

static char	*check_op_rdr_helper(t_minishell *m, char *l, char **s, int x)
{
	char	**sp;
	char	*op;

	pipe(m->redirect);
	sp = ft_split(l, '>');
	if (x == 0)
		op = ft_strdup(*s);
	else
		op = ft_strtrim(sp[0], " ");
	check_op_rdr_helper2(m, l, sp, &op);
	free_s(sp);
	free(m->red);
	close(m->redirect[0]);
	dup2(m->redirect[1], STDOUT_FILENO);
	close(m->redirect[1]);
	free (*s);
	free (l);
	return (op);
}

char	*check_output_redir(char **s, t_minishell *m, int x)
{
	char	**sp;
	char	*op;
	char	*l;
	int		i;

	op = NULL;
	if (x == 1)
		l = ft_strdup(*s);
	else
		l = ft_strdup(m->line);
	if (is_redirection(l, '>'))
		return (check_op_rdr_helper(m, l, s, x));
	else
	{
		free(l);
		return (*s);
	}
}
