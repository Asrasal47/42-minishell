/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:34:07 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 19:12:27 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec(char *argv, char **env, t_minishell *m)
{
	char	**cmd;
	char	*path;
	char	*temp;

	temp = ft_quotes(argv);
	path = set_path(env, temp, &cmd);
	broken_scmd(path, cmd, m);
	if (execve(path, cmd, env) == -1)
		ft_error_cmd(cmd);
}

int	is_redirection(char *str, char c)
{
	int	i;
	int	b;
	int	s;

	i = 0;
	b = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == '\'' && s == 0)
			s++;
		else if (str[i] == '\'' && s == 1)
			s--;
		else if (str[i] == '\"' && b == 0)
			b++;
		else if (str[i] == '\"' && b == 1)
			b--;
		else if (str[i] == '|')
			break ;
		else if (str[i] == c && b == 0 && s == 0)
			return (1);
		i++;
	}
	return (0);
}
