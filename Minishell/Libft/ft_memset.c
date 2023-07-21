/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:44:50 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:13:04 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The memset() function writes len bytes of value c (converted to an 
unsigned char) to the string b. The memset() function returns its 
first argument.*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*ch;

	i = 0;
	ch = (char *)b;
	while (i < len)
	{
		ch[i] = c;
		i++;
	}
	return (b);
}
