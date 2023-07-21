/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:03:10 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:14:03 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strchr() function locates the first occurrence of c (converted to a 
char) in the string pointed to by s.  The terminating null character is 
considered to be part of the string; therefore if c is `\0', the functions 
locate the terminating `\0'. The functions strchr() and strrchr() return a 
pointer to the located character, or NULL if the character does not appear
in the string.*/
char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j] != '\0')
		j++;
	while (i <= j)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
