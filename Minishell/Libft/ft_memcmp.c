/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:30:01 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:11:59 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The memcmp() function compares byte string s1 against byte string s2. 
Both strings are assumed to be n bytes long. The memcmp() function returns
zero if the two strings are identical, otherwise returns the difference 
between the first two differing bytes (treated as unsigned char values, 
so that `\200' is greater than `\0', for example). Zero-length strings are 
always identical.*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	i = 0;
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s3[i] != s4[i])
			return (s3[i] - s4[i]);
		i++;
	}
	return (0);
}
