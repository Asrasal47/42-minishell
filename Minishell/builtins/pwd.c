/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:01:46 by arasal            #+#    #+#             */
/*   Updated: 2023/04/12 18:02:20 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_pwd(void)
{
	char	*s;

	s = NULL;
	s = getcwd(s, PATH_MAX);
	ft_putendl_fd(s, STDOUT_FILENO);
	free(s);
	return (0);
}
