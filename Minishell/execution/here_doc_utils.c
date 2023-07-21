/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:15:15 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 16:16:01 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	here_doc_gnl(t_minishell *m, char **line, char**temp, char *argv)
{
	*line = get_next_line(STDIN_FILENO);
	*temp = ft_quotes(argv);
	if (ft_strcmp(ft_strtrim(*line, "\n"), *temp) == 0)
	{
		free(*line);
		free(*temp);
		exit (0);
	}
	free(*temp);
	*temp = ft_strdup(*line);
	*temp = ft_variable_expansion(*temp, m, 1);
}

static void	here_doc_child(char *argv, int pfd[2], t_minishell *m)
{
	char	*line;
	char	*temp;

	while (1)
	{
		close(pfd[0]);
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("> ", STDOUT_FILENO);
		here_doc_gnl(m, &line, &temp, argv);
		if (!ft_strchr(argv, '\'') && !ft_strchr(argv, '\"'))
			ft_putstr_fd(temp, pfd[1]);
		else
			ft_putstr_fd(line, pfd[1]);
		free(line);
		free(temp);
	}
}

void	here_doc_pipe(char *argv, t_minishell *m)
{
	int		pfd[2];
	int		pid;

	if (pipe(pfd) == -1)
		strerror(EMFILE);
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
		here_doc_child(argv, pfd, m);
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	waitpid(pid, NULL, 0);
}
