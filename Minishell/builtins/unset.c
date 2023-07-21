/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:47:48 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 17:00:33 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_unset_helper(t_minishell *m, char *temp, int i)
{
	if (ft_strncmp(temp, m->e->env_save[i], ft_strlen(temp)) == 0)
	{
		while (m->e->env_save[i + 1])
		{
			free(m->e->env_save[i]);
			m->e->env_save[i] = ft_strdup(m->e->env_save[i + 1]);
			i++;
		}
		free(m->e->env_save[i]);
		m->e->env_save[i] = NULL;
	}
}

int	ft_unset(t_minishell *m)
{
	char	*temp;
	char	**temp2;
	int		i;
	int		j;

	j = 0;
	if (!m->cmds->param && !m->tokens[1])
		return (0);
	if (ft_verify_identifier(m))
		return (1);
	temp2 = ft_split(m->cmds->param, ' ');
	while (temp2[j])
	{
		i = 0;
		temp = ft_strdup(temp2[j]);
		while (m->e->env_save[i])
		{
			ft_unset_helper(m, temp, i);
			i++;
		}
		free(temp);
		j++;
	}
	free_s(temp2);
	return (0);
}
