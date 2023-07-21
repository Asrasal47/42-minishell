/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:39:35 by arasal            #+#    #+#             */
/*   Updated: 2023/04/13 18:07:03 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	var_exp_init(t_var_exp *t, int x)
{
	t->temp = NULL;
	t->temp1 = NULL;
	t->temp2 = NULL;
	t->temp3 = NULL;
	t->xo = x;
}

void	free_var_temp(t_var_exp *t, int a)
{
	if (a == 0)
		free(t->temp);
	free(t->temp1);
	free(t->temp2);
	free(t->temp3);
}
