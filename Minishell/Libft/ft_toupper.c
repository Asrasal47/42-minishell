/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:07:46 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:20:32 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The toupper() function converts a lower-case letter to the corresponding 
upper-case letter. If the argument is a lower-case letter, the toupper() 
function returns the corresponding upper-case letter if there is one; 
otherwise, the argument is returned unchanged.*/
int	ft_toupper(int c)
{
	if ((c >= 97) && (c <= 122))
		c = c - 32;
	return (c);
}
