/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:33:06 by arasal            #+#    #+#             */
/*   Updated: 2023/04/18 18:27:29 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*check_ip_rdr_helper2(t_minishell *m, char **sp, char **s, int x)
{
	char	**sp2;
	char	*op;
	char	*temp;
	int		i;
	int		j;

	j = -1;
	sp2 = NULL;
	while (sp[++j])
	{
		if (sp2)
			free_s(sp2);
		sp2 = ft_split(sp[j], ' ');
		if (sp2[0][1] == ' ')
			i = 1;
		else
			i = 0;
		if (x == 0)
			op = ft_strdup(*s);
		else
			op = ft_strtrim(sp2[i + 1], " ");
		temp = ft_strjoin(op, " ");
		sp2[i] = ft_strtrim(sp2[i], "< ");
		m->redirect[0] = open(sp2[i], O_RDONLY, 0777);
		if (m->redirect[0] == -1)
			ft_error_infile(sp2[i]);
	}
	free_s(sp);
	return (op);
}

static char	*check_ip_rdr_helper(t_minishell *m, char *l, char **s, int x)
{
	char	**sp;
	char	*op;
	char	*temp;

	sp = ft_split(l, '<');
	if (l[0] == '<')
		return (check_ip_rdr_helper2(m, sp, s, x));
	if (x == 0)
		op = ft_strdup(*s);
	else
		op = ft_strtrim(sp[0], " ");
	temp = ft_strjoin(op, " ");
	free(op);
	sp[1] = ft_strtrim(sp[1], " ");
	op = ft_strjoin(temp, sp[1]);
	m->redirect[0] = open(sp[1], O_RDONLY, 0777);
	if (m->redirect[0] == -1)
		ft_error_infile(sp[1]);
	free_s(sp);
	return (op);
}

char	*check_input_redir(char **s, t_minishell *m, int x)
{
	char	*l;
	char	*op;

	if (x == 1)
		l = ft_strdup(*s);
	else
		l = ft_strdup(m->line);
	if (is_redirection(l, '<'))
	{
		pipe(m->redirect);
		op = check_ip_rdr_helper(m, l, s, x);
		close(m->redirect[1]);
		dup2(m->redirect[0], STDIN_FILENO);
		close(m->redirect[0]);
		free(*s);
		free(l);
		return (op);
	}
	else
	{
		free(l);
		return (*s);
	}
}
