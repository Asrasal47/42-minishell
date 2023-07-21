/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:01:56 by arasal            #+#    #+#             */
/*   Updated: 2023/04/15 14:17:00 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_env(char **env_save)
{
	int	i;

	i = 0;
	while (env_save[i] != NULL)
	{
		if (ft_strchr(env_save[i], '='))
			ft_putendl_fd(env_save[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
