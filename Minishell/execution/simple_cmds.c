/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:30:56 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 16:53:52 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	broken_scmd(char *path, char **cmd, t_minishell *m)
{
	if (cmd[0][0] == '\"' || cmd[0][0] == '\'' || !ft_strcmp(cmd[0], ".."))
		exit_error(m->cmd_line, "command not found", 127);
	else if ((!ft_strncmp(cmd[0], "./", 2) || !ft_strncmp(cmd[0], "/", 1))
		&& access(cmd[0], F_OK))
		exit_error(cmd[0], "No such file or directory", 127);
	else if ((!path) || (path && !ft_strncmp(cmd[0], "./", 2)
			&& access(cmd[0], X_OK)))
	{
		if (access(cmd[0], X_OK) && !access(cmd[0], F_OK))
			exit_error(cmd[0], "Permission denied", 126);
		else if (access(cmd[0], F_OK))
			exit_error(cmd[0], "No such file or directory", 127);
		else
			exit_error(cmd[0], "command not found", 127);
	}
	else if (!ft_strcmp(cmd[0], "."))
		exit_error(cmd[0], "filename argument required\n\
.: usage: . filename [arguments]", 127);
	else if (access(cmd[0], F_OK) == 0 && !(cmd[1])
		&& cmd[0][ft_strlen(cmd[0]) - 1] == '/')
		exit_error(cmd[0], "is a directory", 126);
}

static void	exec_simple_helper(t_minishell *m, char **temp, char *s)
{
	if (!ft_strchr(s, ' ') || ft_strnstr(s, "$?", ft_strlen(s)))
		*temp = ft_quotes(s);
	else
		*temp = ft_strdup(s);
	*temp = ft_variable_expansion(*temp, m, 0);
}

void	exec_simple(char *s, t_minishell *m)
{
	char	**cmd;
	char	*path;
	char	*temp;
	pid_t	id;

	exec_simple_helper(m, &temp, s);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		temp = check_output_redir(&temp, m, 1);
		temp = check_input_redir(&temp, m, 1);
		signal(SIGINT, signal_ft);
		signal(SIGQUIT, signal_ft);
		path = set_path(m->e->env_save, temp, &cmd);
		broken_scmd(path, cmd, m);
		cmd_fix(cmd, 0);
		if (execve(path, cmd, m->e->env_save) == -1)
			ft_error_cmd(cmd);
	}
	free(temp);
	collect_exit_status(id, m);
	ft_clear(m);
}
