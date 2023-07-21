/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:40:47 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 23:46:16 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a substring from the string ’s’.
The substring begins at index ’start’ and is of maximum size ’len’.*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s2;
	unsigned int	sublen;
	unsigned int	subcount;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	sublen = 0;
	while (s[start + sublen] != '\0')
		sublen++;
	if (sublen > (unsigned int)len)
		sublen = (unsigned int)len;
	s2 = (char *)malloc(sublen + 1);
	if (!s2)
		return (0);
	subcount = 0;
	while (subcount < sublen)
	{
		s2[subcount] = s[start];
		subcount++;
		start++;
	}
	s2[subcount] = '\0';
	return (s2);
}
