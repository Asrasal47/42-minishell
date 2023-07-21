/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:56:36 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:19:30 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strnstr() function locates the first occurrence of the null-terminated
string needle in the string haystack, where not more than len characters are
searched. Characters that appear after a `\0' character are not searched. If 
needle is an empty string, haystack is returned; if needle occurs nowhere in 
haystack, NULL is returned; otherwise a pointer to the first character of the 
first occurrence of needle is returned.*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;
	size_t	k;

	needle_len = ft_strlen(needle);
	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while ((haystack[i] != '\0') && (i < len))
	{
		k = 0;
		while (haystack[i + k] == needle[k] && (i + k) < len
			&& needle[k] != '\0' && haystack[i + k] != '\0')
			k++;
		if (k == needle_len)
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
