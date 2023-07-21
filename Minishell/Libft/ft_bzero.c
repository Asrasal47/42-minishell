/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:16:50 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:21:48 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The bzero() function writes n zeroed bytes to the string s.  
If n is zero, bzero() does nothing.*/
void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*c;

	i = 0;
	c = s;
	if (n > 0)
	{
		while (i < n)
		{
			c[i] = '\0';
			i++;
		}
	}
}
