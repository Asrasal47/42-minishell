/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:49:44 by arasal            #+#    #+#             */
/*   Updated: 2022/04/11 00:06:22 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The memmove() function copies len bytes from string src to string dst.
The two strings may overlap; the copy is always done in a non-destructive 
manner. The memmove() function returns the original value of dst.*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	char	*s;
	char	*d;

	i = -1;
	s = (char *)src;
	d = (char *)dst;
	if (!d)
		return (NULL);
	if (d < s)
	{
		while (++i < (int)len)
			d[i] = s[i];
	}
	else
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	return (d);
}
