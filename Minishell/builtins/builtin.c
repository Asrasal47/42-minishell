/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:37:32 by arasal            #+#    #+#             */
/*   Updated: 2023/04/17 14:57:34 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_minishell *mshell)
{
	mshell->temp_fd2 = dup(STDOUT_FILENO);
	mshell->temp_fd = dup(STDIN_FILENO);
	mshell->cmds->param = check_output_redir(&mshell->cmds->param, mshell, 0);
	if (ft_strncmp(mshell->cmds->cmd, "echo\0", 5) == 0)
		g_glob.exit_status = print_echo(mshell);
	else if (ft_strncmp(mshell->cmds->cmd, "cd\0", 3) == 0)
		g_glob.exit_status = change_directory(mshell);
	else if (ft_strncmp(mshell->cmds->cmd, "pwd\0", 4) == 0)
		g_glob.exit_status = print_pwd();
	else if (ft_strncmp(mshell->cmds->cmd, "export\0", 7) == 0)
		g_glob.exit_status = save_export(mshell);
	else if (ft_strncmp(mshell->cmds->cmd, "unset\0", 6) == 0)
		g_glob.exit_status = ft_unset(mshell);
	else if (ft_strncmp(mshell->cmds->cmd, "env\0", 4) == 0)
		g_glob.exit_status = print_env(mshell->e->env_save);
	else if (ft_strncmp(mshell->cmds->cmd, "exit\0", 5) == 0)
		ft_exit(mshell);
	if (dup2(mshell->temp_fd, STDIN_FILENO) == -1)
		strerror(EBADF);
	close(mshell->temp_fd);
	if (dup2(mshell->temp_fd2, STDOUT_FILENO) == -1)
		strerror(EBADF);
	close(mshell->temp_fd2);
	ft_clear(mshell);
}

int	check_if_builtin(t_minishell *m, char *argv)
{
	free(m->line);
	m->line = ft_strdup(argv);
	m->tokens = ft_tokenize(argv);
	token_maker(m, 1);
	if (is_builtin(m))
	{
		exec_builtin(m);
		return (1);
	}
	return (0);
}

int	ft_verify_identifier(t_minishell *m)
{
	char	*par;

	par = m->cmds->param;
	if ((!par && m->tokens[1]) || (par && !ft_isalpha(par[0])))
	{
		if (par && par[0] == '$' && par[1] && ft_isalnum(par[1]))
		{
			if (!par[2] || (par[2] && ft_isalpha(par[2])))
				return (0);
		}
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(m->cmds->cmd, STDERR_FILENO);
		ft_putstr_fd(": `", STDERR_FILENO);
		if (par && par[0] == '$' && par[2])
			ft_putstr_fd(par + 2, STDERR_FILENO);
		else
			ft_putstr_fd(par, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static void	check_ex_var_helper(t_minishell *m, int i, char *param, int x)
{
	char	**temp1;

	free(m->e->env_save[i]);
	if (x == 1 && (ft_strchr(m->tokens[1], '\'')
			|| ft_strchr(m->tokens[1], '\"')))
	{
		temp1 = ft_split(m->tokens[1], ' ');
		cmd_fix(temp1, 1);
		m->e->env_save[i] = ft_strdup(temp1[0]);
		if (m->tokens[1][ft_strlen(m->tokens[1]) - 2] == ' ')
			m->e->env_save[i] = ft_strjoin(m->e->env_save[i], " ");
		free_s(temp1);
	}
	else
		m->e->env_save[i] = ft_strdup(param);
}

int	check_ex_var(t_minishell *m, int x)
{
	char	*param;
	char	*temp;
	int		i;

	i = 0;
	param = m->cmds->param;
	if (ft_isalpha(param[0]) && !ft_strchr(param, '=') && x == 1)
		return (0);
	if (ft_isalpha(param[0]) && !ft_strchr(param, '=') && x == 0)
		return (1);
	while (param[i] != '=')
		i++;
	temp = ft_substr(param, 0, i + 1);
	i = -1;
	while (m->e->env_save[++i])
	{
		if (!ft_strncmp(temp, m->e->env_save[i], ft_strlen(temp)))
		{
			check_ex_var_helper(m, i, param, x);
			free(temp);
			return (1);
		}
	}
	free(temp);
	return (0);
}
