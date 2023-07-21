/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:23:23 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 00:26:50 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The memchr() function locates the first occurrence of c (converted to an 
unsigned char) in string s. The memchr() function returns a pointer to the 
byte located, or NULL if no such byte exists within n bytes.*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ss;
	unsigned char	k;

	i = 0;
	ss = (unsigned char *)s;
	k = (unsigned char)c;
	while (n > 0)
	{
		if (ss[i] == k)
			return ((void *)&ss[i]);
		i++;
		n--;
	}
	return (NULL);
}
