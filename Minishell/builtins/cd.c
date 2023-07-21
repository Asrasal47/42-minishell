/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:52:03 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 17:33:55 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	save_pwd_helper(t_minishell *m, int i, int j)
{
	char	**y;

	y = (char **)malloc(sizeof(char *) * i + 1);
	if (!y)
		perror("malloc error");
	y[i] = NULL;
	i = 0;
	while (ft_strncmp(m->e->env_save[i], "PWD=", 4) != 0)
		i++;
	while (++j <= i)
		y[j] = ft_strdup(m->e->env_save[j]);
	y[j++] = ft_strdup(m->cmds->param);
	while (m->e->env_save[j - 1] != NULL)
	{
		y[j] = ft_strdup(m->e->env_save[j - 1]);
		j++;
	}
	free_s(m->e->env_save);
	m->e->env_save = y;
}

static int	save_pwd(t_minishell *m)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (check_ex_var(m, 0))
		return (0);
	while (m->e->env_save[i] != NULL)
		i++;
	i += 1;
	save_pwd_helper(m, i, j);
	return (0);
}

static void	update_pwd(char **temp, t_minishell *m)
{
	free(m->cmds->param);
	free(m->cmds->cmd);
	m->cmds->param = ft_strjoin("OLDPWD=", *temp);
	m->cmds->cmd = ft_strdup("export");
	save_pwd(m);
	free(*temp);
	*temp = NULL;
	*temp = getcwd(*temp, PATH_MAX);
	free(m->cmds->param);
	free(m->cmds->cmd);
	m->cmds->param = ft_strjoin("PWD=", *temp);
	m->cmds->cmd = ft_strdup("export");
	save_pwd(m);
	free(*temp);
}

static int	find_oldpwd(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->e->env_save[i])
	{
		if (!ft_strncmp(m->e->env_save[i], "OLDPWD=", 7))
		{
			free(m->cmds->param);
			m->cmds->param = ft_strdup(m->e->env_save[i] + 7);
			ft_putendl_fd(m->cmds->param, STDOUT_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	change_directory(t_minishell *m)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	temp = getcwd(temp, PATH_MAX);
	if (!m->cmds->param || !ft_strcmp(m->cmds->param, "~"))
	{
		while (ft_strncmp(m->e->env_save[i], "HOME=", 5) != 0)
			i++;
		if (m->cmds->param && !ft_strcmp(m->cmds->param, "~"))
			free(m->cmds->param);
		m->cmds->param = ft_strdup(m->e->env_save[i] + 5);
	}
	if (!ft_strcmp(m->cmds->param, "-"))
	{
		if (!find_oldpwd(m))
			return (no_exit_error(m->cmds->cmd, "OLDPWD not set", 1));
	}
	if (chdir(m->cmds->param))
		perror("chdir fail");
	update_pwd(&temp, m);
	return (0);
}
