/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:50:20 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 00:18:36 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns the last node of the list.*/
t_list	*ft_lstlast(t_list *ori)
{
	t_list	*lst;

	lst = ori;
	while (lst && lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
