/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:20:12 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:10:27 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Iterates the list ’lst’ and applies the function ’f’ on the content of 
each node. Creates a new list resulting of the successive applications of 
the function ’f’. The ’del’ function is used to delete the content of a 
node if needed. Returns the new list or NULL if the allocation fails.*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newnode;
	t_list	*temp;

	temp = lst;
	newlist = NULL;
	while (temp)
	{
		newnode = ft_lstnew(f(temp->content));
		if (newnode)
			ft_lstadd_back(&newlist, newnode);
		else
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		temp = temp->next;
	}
	return (newlist);
}
