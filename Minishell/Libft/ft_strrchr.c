/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:19:44 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:19:47 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The strrchr() function is identical to strchr(),except it locates the last 
occurrence of c. The functions strchr() and strrchr() return a pointer to the
located character, or NULL if the character does not appear in the string.*/
char	*ft_strrchr(const char *s, int c)
{
	int		j;

	j = 0;
	while (s[j] != '\0')
		j++;
	while (j >= 0)
	{
		if (s[j] == (char)c)
			return ((char *)(s + j));
		j--;
	}
	return (0);
}
