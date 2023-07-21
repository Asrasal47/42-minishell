/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:09:16 by arasal            #+#    #+#             */
/*   Updated: 2022/12/30 17:21:23 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strncmp() function compares not more than n characters. Because strncmp() 
is designed for comparing strings rather than binary data, characters that
appear after a `\0' character are not compared. The strncmp() function returns
an integer greater than, equal to, or less than 0, according as the string s1
is greater than, equal to, or less than the string s2. The comparison is done 
using unsigned characters, so that `\200' is greater than `\0'.*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	i = 0;
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (s3[i] != s4[i])
			return ((int)s3[i] - s4[i]);
		if (s3[i] == '\0')
			return (0);
		i++;
		n--;
	}
	return (0);
}
