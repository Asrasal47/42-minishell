/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:57:12 by arasal            #+#    #+#             */
/*   Updated: 2023/04/17 15:01:54 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_declare_x(char *l)
{
	char	*var;
	char	*value;
	int		i;

	i = -1;
	while (l[++i])
		if (l[i] == '=')
			break ;
	var = ft_substr(l, 0, i + 1);
	value = ft_substr(l, i + 1, ft_strlen(l) - i);
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var, STDOUT_FILENO);
	if (ft_strchr(l, '='))
		ft_putstr_fd("\"", STDOUT_FILENO);
	ft_putstr_fd(value, STDOUT_FILENO);
	if (ft_strchr(l, '='))
		ft_putendl_fd("\"", STDOUT_FILENO);
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
	free(var);
	free(value);
}

static void	print_export(char **env)
{
	int		i[2];
	int		arr;
	char	*s;
	char	*lowest;

	i[0] = -1;
	arr = 0;
	while (env[++i[0]])
	{
		s = env[arr];
		i[1] = -1;
		while (env[++i[1]])
		{
			if (i[0] == 0 && ft_strcmp(env[i[1]], s) < 0)
				s = env[i[1]];
			else if (i[0] > 0 && ft_strcmp(env[i[1]], s) < 0
				&& ft_strcmp(env[i[1]], lowest) > 0)
				s = env[i[1]];
		}
		lowest = s;
		ft_declare_x(lowest);
		while (ft_strcmp(lowest, env[arr]) == 0
			|| ft_strcmp(lowest, env[arr]) > 0 && arr < i[0])
			arr++;
	}
}

static void	ft_export_helper(t_minishell *m, int j, char **y, int x)
{
	char	*temp;

	temp = NULL;
	if (!x)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(m->cmds->cmd, STDERR_FILENO);
		ft_putstr_fd(": `", STDERR_FILENO);
		ft_putstr_fd(m->e->env_var[j], STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		free_s(m->e->env_var);
	}
	else
	{
		temp = ft_strjoin(*y, " ");
		free(*y);
		*y = ft_strdup(temp);
		free(temp);
	}
}

static int	save_export_helper(t_minishell *m, int i, int *j)
{
	char	**y;

	while (m->e->env_var[(*j)] != NULL)
		if (!ft_isalpha(m->e->env_var[(*j)++][0]))
			return (1);
	i += (*j);
	y = (char **)malloc(sizeof(char *) * i + 1);
	if (!y)
		perror("malloc error");
	y[i] = NULL;
	i -= 1;
	y[i] = ft_strdup(m->e->env_save[i - (*j)]);
	while ((*j) > 0)
	{
		y[--i] = ft_strtrim(ft_variable_expansion(m->e->env_var[--(*j)],
					m, 1), "\n");
		if (m->tokens[1][ft_strlen(m->tokens[1]) - 2] == ' ' && (*j) == 0)
			ft_export_helper(m, 0, &y[i], 1);
	}
	while (--i >= 0)
		y[i] = ft_strdup(m->e->env_save[i]);
	free_s(m->e->env_save);
	free_s(m->e->env_var);
	m->e->env_save = &(*y);
	return (0);
}

int	save_export(t_minishell *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((!m->cmds->param && !m->tokens[1]) || !m->e->env_save[0])
	{
		print_export(m->e->env_save);
		return (0);
	}
	if (ft_verify_identifier(m))
		return (1);
	if (check_ex_var(m, 1))
		return (0);
	while (m->e->env_save[i] != NULL)
		i++;
	m->e->env_var = ft_split(m->tokens[1], ' ');
	cmd_fix(m->e->env_var, 1);
	if (save_export_helper(m, i, &j))
	{
		ft_export_helper(m, j - 1, NULL, 0);
		return (1);
	}
	return (0);
}
