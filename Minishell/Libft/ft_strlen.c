/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:47:51 by arasal            #+#    #+#             */
/*   Updated: 2023/01/06 21:43:02 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strlen() function computes the length of the string s. The strnlen() 
function attempts to compute the length of s, but never scans beyond the 
first maxlen bytes of s.*/
size_t	ft_strlen(const char *s)
{
	size_t	t;

	t = 0;
	while (s[t] != '\0')
		t++;
	return (t);
}
