/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:16:14 by arasal            #+#    #+#             */
/*   Updated: 2023/04/18 19:00:32 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_ft(int sign)
{
	if (sign == SIGQUIT && g_glob.pid == 0)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_glob.exit_status = 131;
	}
	else if (sign == SIGINT && g_glob.pid == 0)
	{
		ft_putchar_fd('\n', 1);
		g_glob.exit_status = 130;
	}
}

void	signals_handler(int sign)
{
	struct termios	t;
	int				fd;

	fd = 0;
	tcgetattr(fd, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(fd, TCSANOW, &t);
	if (sign > 0)
		g_glob.exit_status = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_redisplay();
}

char	**save_env(char **env)
{
	int		i;
	char	**env_save;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	env_save = malloc(sizeof(char *) * i + 1);
	if (!env_save)
		perror("malloc error");
	env_save[i] = NULL;
	while (--i >= 0)
	{
		env_save[i] = ft_strdup(env[i]);
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			env_save[i][6] = env[i][6] + 1;
	}
	return (env_save);
}

void	collect_exit_status(int child_pid, t_minishell *m)
{
	int	status;

	waitpid(child_pid, &status, WUNTRACED | WCONTINUED);
	if (WIFEXITED(status))
		g_glob.exit_status = WEXITSTATUS(status);
	else if (WTERMSIG(status) == SIGQUIT || WTERMSIG(status) == SIGINT)
	{
		g_glob.exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("^\\Quit: 3", STDOUT_FILENO);
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (WIFSIGNALED(status))
		g_glob.exit_status = 128 + WTERMSIG(status);
	sigaction(SIGINT, &m->sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	struct_init(t_minishell *mshell, int argc, char **env)
{
	mshell->count = argc;
	mshell->pipes = 0;
	mshell->line = NULL;
	mshell->cmd_line = NULL;
	mshell->last_line = NULL;
	mshell->red = NULL;
	mshell->e = malloc(sizeof(t_env));
	mshell->e->env_save = save_env(env);
	mshell->cmds = malloc(sizeof(t_b));
	mshell->cmds->cmd = NULL;
	mshell->cmds->param = "OLDPWD";
	mshell->cmds->option = NULL;
	g_glob.pid = 0;
	if (!mshell->e || !mshell->e->env_save || !mshell->cmds)
		return (1);
	ft_unset(mshell);
	mshell->cmds->param = NULL;
	return (0);
}
