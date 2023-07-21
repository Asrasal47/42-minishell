/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:08:29 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 17:09:09 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cmd_fix_helper(char ***cmd, int i)
{
	char	*temp;
	char	*temp2;
	int		j;

	temp = ft_strtrim((*cmd)[i], "\'\"");
	free((*cmd)[i]);
	(*cmd)[i] = ft_strdup(temp);
	free(temp);
	j = 1;
	while ((*cmd)[i + j])
	{
		temp = ft_strtrim((*cmd)[i + j], "\'\"");
		free((*cmd)[i + j]);
		(*cmd)[i + j] = ft_strdup(temp);
		free(temp);
		temp = ft_strjoin(" ", (*cmd)[i + j]);
		temp2 = ft_strjoin((*cmd)[i], temp);
		free((*cmd)[i]);
		(*cmd)[i] = ft_strdup(temp2);
		free((*cmd)[i + j]);
		free(temp);
		free(temp2);
		j++;
	}
}

static void	cmd_fix_helper2(char ***cmd, int i)
{
	char	*temp;

	temp = ft_quotes((*cmd)[i]);
	free((*cmd)[i]);
	(*cmd)[i] = ft_strtrim(temp, " ");
	free(temp);
}

static void	quote_counter(char c, int *k, int *l)
{
	if (c == '\"')
		*k += 1;
	if (c == '\'')
		*l += 1;
}

void	cmd_fix(char **cmd, int x)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = -1;
	k = 0;
	l = 0;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
			quote_counter(cmd[i][j], &k, &l);
		if ((k % 2 == 1 || l % 2 == 1) && cmd[i + 1]
			&& !ft_strchr(cmd[i + 1], '='))
		{
			cmd_fix_helper(&cmd, i);
			if (x)
				cmd_fix_helper2(&cmd, i);
			cmd[i + 1] = NULL;
		}
		else
			cmd_fix_helper2(&cmd, i);
	}
}
