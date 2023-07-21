/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:46:51 by arasal            #+#    #+#             */
/*   Updated: 2023/04/17 15:01:30 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_exit_numericarg(t_minishell *m)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(m->cmds->cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(m->cmds->param, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	g_glob.exit_status = 255;
}

void	ft_exit(t_minishell *m)
{
	if ((m->cmds->param && ft_atoi(m->cmds->param) == 0
			&& m->cmds->param[0] != '0') || (!m->cmds->param && m->tokens[1]))
		ft_exit_numericarg(m);
	else if (m->cmds->param && ft_atoi(m->cmds->param) != 0)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		if (ft_strchr(m->cmds->param, ' '))
			g_glob.exit_status = 1;
		else if (ft_atoi(m->cmds->param) < 0)
			g_glob.exit_status = 256 - (-(ft_atoi(m->cmds->param)) % 256);
		else
			g_glob.exit_status = ft_atoi(m->cmds->param) % 256;
	}
	else if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDOUT_FILENO);
	ft_clear(m);
	free(m->last_line);
	free_s(m->e->env_save);
	free(m->e);
	free(m->cmds);
	exit(g_glob.exit_status);
}
