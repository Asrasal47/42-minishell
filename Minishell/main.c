/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:53:06 by arasal            #+#    #+#             */
/*   Updated: 2023/04/18 19:00:03 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static	int	check_empty_cmd(char *cmd, char *c)
{
	int		i;
	int		n;
	char	*s;

	i = 0;
	n = 0;
	s = ft_strtrim(cmd, c);
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			n++;
		i++;
	}
	free(s);
	if (n == 0)
		return (1);
	if (c[0] == '\"')
		return (check_empty_cmd(cmd, "\'"));
	return (0);
}

static int	ft_prompt_helper(t_minishell *m)
{
	if (check_empty_cmd(m->line, "\""))
	{
		free(m->line);
		free(m->cmd_line);
		ft_putendl_fd("minishell: command not found", STDERR_FILENO);
		g_glob.exit_status = 127;
		return (1);
	}
	if (m->line[0] && (!m->last_line || (m->last_line
				&& ft_strcmp(m->line, m->last_line))))
	{
		free(m->last_line);
		m->last_line = NULL;
		m->last_line = ft_strdup(m->line);
		add_history(m->line);
	}
	return (0);
}

static int	ft_prompt(t_minishell *m)
{
	char	*temp;

	if (isatty(STDIN_FILENO))
		m->cmd_line = readline("\033[31marasal@\033[32mminishell$ ");
	else
	{
		m->cmd_line = get_next_line(fileno(stdin));
		temp = ft_strdup(m->cmd_line);
		free(m->cmd_line);
		m->cmd_line = ft_strtrim(temp, "\n");
		free(temp);
	}
	if (!m->cmd_line)
		return (2);
	m->line = ft_strtrim(m->cmd_line, " \t\r\n");
	if (ft_strlen(m->line) == 0)
	{
		free(m->line);
		free(m->cmd_line);
		return (1);
	}
	if (ft_prompt_helper(m))
		return (1);
	return (0);
}

static int	ft_loop_cmds(t_minishell *m)
{
	int	prompt;

	prompt = ft_prompt(m);
	if (prompt == 2 && isatty(STDIN_FILENO))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (0);
	}
	if (prompt == 2)
		return (0);
	else if (prompt == 1)
		return (1);
	if (!verify_syntax(m))
	{
		ft_putstr_fd("minishell: syntax error near \
unexpected token `", STDERR_FILENO);
		ft_putstr_fd("newline", STDERR_FILENO);
		ft_putendl_fd("\'", STDERR_FILENO);
		return (1);
	}
	if (!token_maker(m, 0))
		return (0);
	if (!parse_command(m))
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	mshell;
	int			i;

	(void)argv;
	if (argc >= 2)
	{
		dprintf(2, "%s : %s\n", argv[1], strerror(2));
		return (EXIT_FAILURE);
	}
	if (struct_init(&mshell, argc, env))
		return (EXIT_FAILURE);
	mshell.sa.sa_handler = signals_handler;
	mshell.sa.sa_flags = 0;
	sigaction(SIGINT, &mshell.sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	while (ft_loop_cmds(&mshell))
		;
	return (g_glob.exit_status);
}
