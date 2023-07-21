/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:44:18 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 00:22:25 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Counts the number of nodes in a list and returns the length of the list*/
int	ft_lstsize(t_list *lst)
{
	int	lstlen;

	lstlen = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		lstlen++;
	}
	return (lstlen);
}
