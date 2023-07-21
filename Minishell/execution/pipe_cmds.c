/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:57:14 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 19:13:36 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_pipe_helper(t_minishell *m, int x)
{
	if (x)
	{
		signal(SIGINT, signal_ft);
		signal(SIGQUIT, signal_ft);
	}
	else
	{
		close(m->file[1]);
		if (dup2(m->file[0], STDIN_FILENO) == -1)
			strerror(EBADF);
		close(m->file[0]);
	}
}

void	exec_lst_pipe(char *s, t_minishell *m)
{
	char	**cmd;
	char	*path;
	char	*temp;
	pid_t	id;

	temp = ft_quotes(s);
	temp = ft_variable_expansion(temp, m, 0);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		ft_pipe_helper(m, 1);
		temp = check_output_redir(&temp, m, 1);
		temp = check_input_redir(&temp, m, 1);
		path = set_path(m->e->env_save, temp, &cmd);
		broken_scmd(path, cmd, m);
		if (check_if_builtin(m, s))
			exit(g_glob.exit_status);
		if (execve(path, cmd, m->e->env_save) == -1)
			ft_error_cmd(cmd);
	}
	free(temp);
	collect_exit_status(id, m);
}

void	ft_pipe(char *argv, t_minishell *m)
{
	int		pid;

	if (pipe(m->file) == -1)
		strerror(EMFILE);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		ft_pipe_helper(m, 1);
		close(m->file[0]);
		if (dup2(m->file[1], STDOUT_FILENO) == -1)
			strerror(EBADF);
		close(m->file[1]);
		argv = check_output_redir(&argv, m, 1);
		argv = check_input_redir(&argv, m, 1);
		if (check_if_builtin(m, argv))
			exit(g_glob.exit_status);
		ft_exec(argv, m->e->env_save, m);
	}
	ft_pipe_helper(m, 0);
}

static void	close_temp_fds(t_minishell *m)
{
	if (dup2(m->temp_fd, STDIN_FILENO) == -1)
		strerror(EBADF);
	close(m->temp_fd);
	if (dup2(m->temp_fd2, STDOUT_FILENO) == -1)
		strerror(EBADF);
	close(m->temp_fd2);
}

void	parsing_pipe(t_minishell *m)
{
	int		i;
	int		c;
	char	*temp;
	char	**comm;

	c = 0;
	comm = ft_split(m->line, '|');
	m->temp_fd = dup(STDIN_FILENO);
	m->temp_fd2 = dup(STDOUT_FILENO);
	while (comm[c] != NULL)
	{
		temp = comm[c];
		free(comm[c]);
		comm[c++] = ft_strtrim(temp, " ");
	}
	i = 0;
	while (comm[i + 1] != NULL)
		ft_pipe(comm[i++], m);
	exec_lst_pipe(comm[i], m);
	close_temp_fds(m);
	free_s(comm);
	free(m->line);
}
