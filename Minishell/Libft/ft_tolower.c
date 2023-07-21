/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:41:02 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:20:14 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The tolower() function converts an upper-case letter to the corresponding
lower-case letter. If the argument is an upper-case letter, the tolower() 
function returns the corresponding lower-case letter if there is one; 
otherwise, the argument is returned unchanged.*/
int	ft_tolower(int c)
{
	if ((c >= 65) && (c <= 90))
		c = c + 32;
	return (c);
}
