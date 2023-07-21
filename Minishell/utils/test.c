/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:51:56 by arasal            #+#    #+#             */
/*   Updated: 2023/04/17 14:41:13 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clear(t_minishell *m)
{
	free_s(m->tokens);
	if (m->line)
		free(m->line);
	if (m->cmds->cmd)
		free(m->cmds->cmd);
	if (m->cmds->option)
		free_s(m->cmds->option);
	if (m->cmds->param)
		free(m->cmds->param);
	m->line = NULL;
	m->cmds->cmd = NULL;
	m->cmds->param = NULL;
	m->cmds->option = NULL;
}

void	print_s(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		ft_putendl_fd(str[i], STDOUT_FILENO);
		i++;
	}
}

void	*free_s(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (!str[0])
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	while (str[i] != NULL)
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
	return (NULL);
}

void	*free_r(char *str)
{
	if (str == NULL)
		return (NULL);
	free(str);
	str = NULL;
	return (NULL);
}
