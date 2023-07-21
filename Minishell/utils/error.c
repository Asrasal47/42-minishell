/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 03:22:51 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 14:51:45 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(char *cmd, char *error_msg, int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(exit_status);
}

int	no_exit_error(char *cmd, char *error_msg, int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	return (exit_status);
}

void	ft_error_infile(char	*file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("No such file or directory", STDERR_FILENO);
	g_glob.exit_status = 1;
	exit(g_glob.exit_status);
}

void	ft_error_outfile(char	*file)
{
	if (access(file, W_OK) != 0)
		ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putendl_fd(file, 2);
	exit(0);
}

void	ft_error_cmd(char **cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}
