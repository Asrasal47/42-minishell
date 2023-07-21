/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:10:01 by arasal            #+#    #+#             */
/*   Updated: 2023/04/12 20:10:36 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_path(char **env)
{
	int		i;
	char	**e;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=/", 6) != 0)
		i++;
	if (!env[i])
		return (-1);
	return (i);
}

static void	set_path_helper(char **path, char ***path1, char ***cmd)
{
	int	i;

	i = 0;
	while ((*path1)[i] != NULL)
	{
		*path = ft_strjoin((*path1)[i++], "/");
		*path = ft_strjoin(*path, *cmd[0]);
		if (!access(*path, F_OK))
			break ;
		free(*path);
	}
	free_s(*path1);
}

char	*set_path(char **env, char *str, char ***cmd)
{
	char	**path1;
	char	*path;
	int		i;

	i = find_path(env);
	if (i == -1)
	{
		*cmd = ft_split(str, ' ');
		if (!access(*cmd[0], F_OK) && !access(*cmd[0], X_OK))
		{
			path = ft_strdup(*cmd[0]);
			return (path);
		}
		return (NULL);
	}
	path1 = ft_split(env[i], '=');
	path1 = ft_split(path1[1], ':');
	*cmd = ft_split(str, ' ');
	if (!access(*cmd[0], F_OK))
	{
		free_s(path1);
		return (*cmd[0]);
	}
	set_path_helper(&path, &path1, cmd);
	return (path);
}
