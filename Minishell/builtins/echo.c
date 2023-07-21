/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:10:14 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 20:22:33 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_echo_option(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->cmds->param[i])
	{
		if (m->cmds->param[i] == '\t')
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
			while (m->cmds->param[i + 1] && m->cmds->param[i + 1] == '\t')
				i++;
		}
		else
			ft_putchar_fd(m->cmds->param[i], STDOUT_FILENO);
		i++;
	}
}

static void	print_echo_no_option(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->cmds->param[i])
	{
		if (m->cmds->param[i] == '\t')
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
			while (m->cmds->param[i + 1] && m->cmds->param[i + 1] == '\t')
				i++;
		}
		else
			ft_putchar_fd(m->cmds->param[i], STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	print_echo(t_minishell *m)
{
	if (!m->cmds->param)
	{
		if (!m->cmds->option)
			ft_putchar_fd('\n', 1);
		return (0);
	}
	if (m->cmds->option)
		print_echo_option(m);
	else
		print_echo_no_option(m);
	return (0);
}
