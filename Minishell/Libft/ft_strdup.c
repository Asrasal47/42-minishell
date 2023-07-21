/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:25:43 by arasal            #+#    #+#             */
/*   Updated: 2022/12/28 10:06:09 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strdup() function allocates sufficient memory for a copy of the 
string s1, does the copy, and returns a pointer to it.  The pointer may 
subsequently be used as an argument to the function free(3). If insufficient 
memory is available, NULL is returned and errno is set to ENOMEM. The 
strndup() function copies at most n characters from the string s1 always 
NULL terminating the copied string.*/
char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	s2 = (char *)malloc(i + 1);
	if (!s2)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
